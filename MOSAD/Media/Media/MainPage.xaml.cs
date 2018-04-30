using System;
using Windows.Storage;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.ViewManagement;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Data;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace Media
{
    public class Myr : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            // 在 thumb 旁显示的当前值的后面加一个百分号
            return value + "s";
        }

        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return null;
        }
    }
    public class PAndS : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, string language)
        {
            return TimeSpan.FromSeconds((double)value);
        }
        public object ConvertBack(object value, Type targetType, object parameter, string language)
        {
            return (int)(((TimeSpan)value).TotalSeconds);
        }
    }

    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {
        public MainPage()
        {
            this.InitializeComponent();
        }

        private void VolumeAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            FrameworkElement ele = sender as FrameworkElement;
            if (e != null)
            {
                FlyoutBase.ShowAttachedFlyout(ele);
                Volume.ValueChanged += Volume_ValueChanged;
            }
        }

        private void PlayAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            TimeSpan total = Player.NaturalDuration.TimeSpan;
            Player.Play();
            Player.Volume = (double)Volume.Value;
            TimeSpan start = TimeSpan.FromSeconds(0);
            if (!(Player.Position < total))
            {
                process.Value = 0;
            }
            if (Player.Position != start)
            {
                InnerEllStoryboard.Begin();

            }
            else
            {
                if (!Player.IsAudioOnly)
                {
                    Innerellipse.Visibility = Visibility.Collapsed;
                    Outerellipse.Visibility = Visibility.Collapsed;
                    Brush.Visibility = Visibility.Collapsed;
                    InnerEllStoryboard.Stop();
                }
                else
                {
                    Innerellipse.Visibility = Visibility.Visible;
                    Outerellipse.Visibility = Visibility.Visible;
                    Brush.Visibility = Visibility.Visible;
                    InnerEllStoryboard.Begin();
                }
            }
        }
        private void PauseAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            Player.Pause();
            InnerEllStoryboard.Pause();
        }

        private void StopAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            Player.Stop();
            InnerEllStoryboard.Stop();
            process.Value = 0;
        }

        private async void SelectAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            FileOpenPicker open = new FileOpenPicker();
            // Open a stream for the selected file 
            open.FileTypeFilter.Add(".AVI");
            open.FileTypeFilter.Add(".MP4");
            open.FileTypeFilter.Add(".WMV");
            open.FileTypeFilter.Add(".MP3");
            StorageFile file = await open.PickSingleFileAsync();
            // Ensure a file was selected 
            if (file != null)
            {
                using (IRandomAccessStream stream = await file.OpenAsync(FileAccessMode.Read))
                {
                    Player.SetSource(stream, file.FileType);
                }
                Player.AutoPlay = true;
                process.Value = 0;
                if (IsMusic(file.FileType))
                {
                    Innerellipse.Visibility = Visibility.Visible;
                    Outerellipse.Visibility = Visibility.Visible;
                    Brush.Visibility = Visibility.Visible;
                    InnerEllStoryboard.Begin();
                    Player.IsFullWindow = false;
                }
                else
                {
                    // video
                    InnerEllStoryboard.Stop();
                    Innerellipse.Visibility = Visibility.Collapsed;
                    Outerellipse.Visibility = Visibility.Collapsed;
                    Brush.Visibility = Visibility.Collapsed;
                    Player.IsFullWindow = true;
                }
            }
        }

        private bool IsMusic(string fileType)
        {
            return (fileType == ".mp3" || fileType == ".wav" || fileType == ".m4b" || fileType == ".m4a" || fileType == ".wma");
        }

        private void FullAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            ApplicationView view = ApplicationView.GetForCurrentView();

            bool isfull = view.IsFullScreenMode;

            if (isfull)
            {
                view.ExitFullScreenMode();
            }
            else
            {
                view.TryEnterFullScreenMode();
            }
        }

        private void Volume_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            Player.Volume = Volume.Value / 100;
        }

        private void process_Loaded(object sender, RoutedEventArgs e)
        {
            double seconds = (Player.Position.TotalSeconds);
            process.Value = seconds;
        }

        private void me_MediaOpened(object sender, RoutedEventArgs e)
        {
            process.Maximum = (int)Player.NaturalDuration.TimeSpan.TotalSeconds;
        }

        private void Player_DoubleTapped(object sender, Windows.UI.Xaml.Input.DoubleTappedRoutedEventArgs e)
        {
            FullAppBarButton_Click(sender, e as RoutedEventArgs);
        }
    }
}
