import grpclib
import grpclib.server
from grpclib.server import Server

# from grpclib.reflection.service import ServerReflection
from concurrent import futures
import os
import uuid
from typing import AsyncIterator
from proto.lib.filestream import (
    HashAlgorithm,
    TransferBase,
    Image,
    FrameMeta,
    ImageChunk,
    TransferResponse,
)
import hashlib
import platform
import asyncio

import elasticapm


async def StartServer(*, host=None):

    WORKER_THREADS = int(str(os.getenv("WORKER_THREADS", 10)))
    INSECURE_GRPC_PORT = int(str(os.getenv("INSECURE_GRPC_PORT", 50051)))
    SECURE_GRPC_PORT = int(str(os.getenv("SECURE_GRPC_PORT", 50052)))
    GRPC_REFLECTION = True

    if GRPC_REFLECTION:

        services = [GRPCService()]
        # services = ServerReflection.extend(services)
        server = Server(services)
    else:
        server = Server([GRPCService()])

    # Note: graceful_exit isn't supported in Windows
    print("Server starting")
    if platform.system() == "Windows":
        await server.start(
            host, INSECURE_GRPC_PORT, reuse_address=True, reuse_port=False
        )
        await server.wait_closed()
    else:
        with grpclib.utils.graceful_exit([server]):
            await server.start(host, INSECURE_GRPC_PORT)
            print("Server Started")
            await server.wait_closed()


class GRPCService(TransferBase):
    def __init__(self, hook=None):
        self.hook = hook
        self.client = elasticapm.Client(
            service_name="debayer grpc", server_url="http://elk.infarm.io:8200"
        )
        elasticapm.instrument()

    async def file_stream(
        self, frame_meta: "FrameMeta", image_chunk: "ImageChunk"
    ) -> "TransferResponse":
        self.client.begin_transaction(transaction_type="grpc request")
        response: TransferResponse = TransferResponse()
        response.image_hash.file_hash = str(
            hashlib.md5(image_chunk.frame_chunk).hexdigest()
        )
        response.image_hash.hash_algorithm = HashAlgorithm.MD5
        response.size = len(image_chunk.frame_chunk)
        self.client.end_transaction(name=__name__, result="success")
        return response


if __name__ == "__main__":
    asyncio.run(StartServer())