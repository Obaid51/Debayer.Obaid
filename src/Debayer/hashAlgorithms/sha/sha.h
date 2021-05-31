#ifndef SHA_H
#define SHA_H

#include <sstream>
#include <iomanip>
#include <functional>

#define CH(x,y,z)     ((x & y) ^ (~x & z))
#define MAJ(x,y,z)    ((x & y) ^ (x & z) ^ (y & z))
#define PARITY(x,y,z) (x ^ y ^ z)
#define ROTR_32(x,n)  ((x >> n) | (x << (32 - n)))
#define ROTR_64(x,n)  ((x >> n) | (x << (64 - n)))
#define ROTL_32(x,n)  ((x << n) | (x >> (32 - n)))
#define _SHR(x,n)      (x >> n)
#define S0_256(x) (ROTR_32(x, 2) ^ ROTR_32(x,13) ^ ROTR_32(x,22))
#define S0_512(x) (ROTR_64(x,28) ^ ROTR_64(x,34) ^ ROTR_64(x,39))
#define S1_256(x) (ROTR_32(x, 6) ^ ROTR_32(x,11) ^ ROTR_32(x,25))
#define S1_512(x) (ROTR_64(x,14) ^ ROTR_64(x,18) ^ ROTR_64(x,41))
#define s0_256(x) (ROTR_32(x, 7) ^ ROTR_32(x,18) ^ _SHR(x, 3))
#define s0_512(x) (ROTR_64(x, 1) ^ ROTR_64(x, 8) ^ _SHR(x, 7))
#define s1_256(x) (ROTR_32(x,17) ^ ROTR_32(x,19) ^ _SHR(x,10))
#define s1_512(x) (ROTR_64(x,19) ^ ROTR_64(x,61) ^ _SHR(x, 6))

const uint32_t K_256[64] {
  0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
  0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
  0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3,
  0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
  0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc,
  0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
  0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
  0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
  0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13,
  0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
  0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3,
  0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
  0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
  0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
  0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208,
  0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

const uint64_t K_512[80] {
  0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc,
  0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118,
  0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2,
  0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694,
  0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65,
  0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5,
  0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4,
  0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70,
  0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df,
  0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b,
  0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30,
  0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8,
  0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8,
  0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3,
  0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec,
  0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b,
  0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178,
  0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b,
  0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c,
  0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

const uint32_t K[80] {
  0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
  0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
  0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
  0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
  0x5a827999, 0x5a827999, 0x5a827999, 0x5a827999,
  0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
  0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
  0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
  0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
  0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1, 0x6ed9eba1,
  0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
  0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
  0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
  0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
  0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc, 0x8f1bbcdc,
  0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6,
  0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6,
  0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6,
  0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6,
  0xca62c1d6, 0xca62c1d6, 0xca62c1d6, 0xca62c1d6};


std::string sha1(std::string);
std::string sha224(std::string);
std::string sha256(std::string);
std::string sha384(std::string);
std::string sha512(std::string);

#endif // SHA256_H
