Imports Azure.Storage.Blobs
Imports Azure.Storage.Blobs.Models
Imports DevExpress.Data
Imports DevExpress.Utils.Design
Imports DevExpress.Utils.Drawing
Imports DevExpress.Utils.Menu
Imports DevExpress.Utils.Svg
Imports System
Imports System.Collections.Generic
Imports System.Data
Imports System.Drawing
Imports System.Drawing.Imaging
Imports System.IO
Imports System.Linq

Namespace DXApplication
	Partial Public Class Main
		Inherits DevExpress.XtraEditors.XtraForm

		Private containerClient As BlobContainerClient
		Private images As List(Of Image)
		Public Sub New()
			InitializeComponent()

			InitContainerClient()

			unboundImageSource.Properties.Add(New UnboundSourceProperty("Image", GetType(Image)))
			gridControl.DataSource = unboundImageSource
		End Sub
		Private Sub InitContainerClient()
			Dim blobServiceClient = New BlobServiceClient(ConnectionSettings.ConnectionSring)
			containerClient = blobServiceClient.GetBlobContainerClient(ConnectionSettings.BlobContainerName)
		End Sub
		Private Async Sub OnLoadImagesButtonClick(ByVal sender As Object, ByVal e As DevExpress.XtraBars.ItemClickEventArgs) Handles barButtonItem1.ItemClick
			Dim fileNames = containerClient.GetBlobs().Select(Function(item) item.Name).ToList()

			images = New List(Of Image)(fileNames.Count)
			unboundImageSource.SetRowCount(fileNames.Count)
			Dim palette = SvgPaletteHelper.GetSvgPalette(LookAndFeel, ObjectState.Normal)

			For Each fileName In fileNames
				Dim blobClient As BlobClient = containerClient.GetBlobClient(fileName)
				Dim download As BlobDownloadInfo = Await blobClient.DownloadAsync()
				Using stream = New MemoryStream()
					Await download.Content.CopyToAsync(stream)
					images.Add(GetImage(stream, palette))
					gridView.RefreshRow(images.Count - 1)
				End Using
			Next fileName
		End Sub
		Private Function GetImage(ByVal stream As MemoryStream, ByVal palette As ISvgPaletteProvider) As Image
			Dim img As Image = Nothing
			Try
				stream.Position = 0
				img = SvgImage.FromStream(stream).Render(palette)
			Catch
			End Try
			Return img
		End Function
		Private Sub OnValueNeeded(ByVal sender As Object, ByVal e As UnboundSourceValueNeededEventArgs) Handles unboundImageSource.ValueNeeded
			If e.RowIndex < images.Count Then
				e.Value = images(e.RowIndex)
			End If
		End Sub
		Private Sub OnPopupMenuShowing(ByVal sender As Object, ByVal e As DevExpress.XtraEditors.Events.PopupMenuShowingEventArgs) Handles pictureEdit.PopupMenuShowing
			e.RestoreMenu = True
			e.PopupMenu.Items.Add(New DXMenuItem("Upload to Azure Blob Storage", AddressOf OnMenuItemClick))
		End Sub
		Private Async Sub OnMenuItemClick(ByVal sender As Object, ByVal e As EventArgs)
			If pictureEdit.Image IsNot Nothing Then
				Dim fileName As String = $"TestImage{Guid.NewGuid()}.png"
				Dim blobClient As BlobClient = containerClient.GetBlobClient(fileName)
				Using uploadStream = New MemoryStream()
					pictureEdit.Image.Save(uploadStream, ImageFormat.Png)
					uploadStream.Position = 0
					Await blobClient.UploadAsync(uploadStream)
				End Using
			End If
		End Sub
	End Class
End Namespace
