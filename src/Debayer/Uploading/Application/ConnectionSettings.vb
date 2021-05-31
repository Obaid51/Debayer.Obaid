Imports System
Imports System.Collections.Generic
Imports System.Linq
Imports System.Text
Imports System.Threading.Tasks

Namespace DXApplication
	Public Module ConnectionSettings
		Public ConnectionSring, BlobContainerName As String
		Public Sub SetUp(ByVal connectionString As String, ByVal blobContainerName As String)
			ConnectionSring = connectionString
			ConnectionSettings.BlobContainerName = blobContainerName
		End Sub
	End Module
End Namespace
