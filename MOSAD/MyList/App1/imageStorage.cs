using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Windows.Security.Cryptography;
using Windows.Security.Cryptography.Core;
using Windows.Storage;
using Windows.Storage.Streams;
using Windows.UI.Xaml.Media.Imaging;

namespace MyList
{
    public static class ImageStorage
    {
        public static async Task GetLoacalFolderImage(Uri uri, BitmapImage timg)
        {
            StorageFolder folder = await GetImageFolder();
            string name = Md5(uri.AbsolutePath);
            try
            {
                StorageFile file = await folder.GetFileAsync(name);
                using (var stream = await file.OpenAsync(FileAccessMode.Read))
                {
                    await timg.SetSourceAsync(stream);
                }
            }
            catch (Exception)
            {
            }
        }

        public static async Task StorageImageFolder(IRandomAccessStream stream, Uri uri)
        {
            StorageFolder folder = await GetImageFolder();
            string image = Md5(uri.AbsolutePath);
            try
            {
                StorageFile file = await folder.CreateFileAsync(image);
                await FileIO.WriteBytesAsync(file, await ConvertIRandomAccessStreamByte(stream));
            }
            catch (Exception)
            {
            }
        }

        private static async Task<byte[]> ConvertIRandomAccessStreamByte(IRandomAccessStream stream)
        {
            DataReader read = new DataReader(stream.GetInputStreamAt(0));
            await read.LoadAsync((uint)stream.Size);
            byte[] temp = new byte[stream.Size];
            read.ReadBytes(temp);
            return temp;
        }

        private static async Task<StorageFolder> GetImageFolder()
        {
            string name = "image";
            StorageFolder folder = null;
            try
            {
                folder = await ApplicationData.Current.LocalFolder.GetFolderAsync(name);
            }
            catch (FileNotFoundException)
            {
                folder = await ApplicationData.Current.LocalFolder.CreateFolderAsync(name);
            }
            return folder;
        }

        private static string Md5(string str)
        {
            HashAlgorithmProvider hashAlgorithm = HashAlgorithmProvider.OpenAlgorithm(HashAlgorithmNames.Md5);
            CryptographicHash cryptographic = hashAlgorithm.CreateHash();
            IBuffer buffer = CryptographicBuffer.ConvertStringToBinary(str, BinaryStringEncoding.Utf8);
            cryptographic.Append(buffer);
            return CryptographicBuffer.EncodeToHexString(cryptographic.GetValueAndReset());
        }
    }
}
