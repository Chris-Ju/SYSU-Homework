using System;
using System.IO;
using System.Linq;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Windows.UI.Xaml.Controls.Primitives;
using Windows.UI.Xaml.Navigation;
using Windows.Storage.Pickers;
using Windows.Storage.Streams;
using Windows.UI.Xaml.Media;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Media.Imaging;
using Windows.Storage;
using Windows.Storage.AccessCache;
using Windows.UI.Core;
using Windows.UI.Input;
using Windows.Data.Xml.Dom;
using Windows.UI.Notifications;
using SQLitePCL;
using System.Collections.ObjectModel;
using Newtonsoft.Json;
using System.Net.Http;
using Windows.Devices.Geolocation;
using Windows.UI.ViewManagement;
using MyDiary.Models;
using System.Diagnostics;
using Windows.UI.Popups;

// https://go.microsoft.com/fwlink/?LinkId=234238 上介绍了“空白页”项模板

namespace MyDiary
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class NewPage : Page
    {
        ObservableCollection<String> tags = new ObservableCollection<String>();

        public Models.ListItem Item;
        private int ID;
        public string filePath = "";
        public StorageFile file;
        private bool create;
        DateTime lastdate = DateTime.Now;
        public NewPage() {
            var db = App.conn;
            using (var statement = db.Prepare("SELECT * FROM Tags"))
            {
                while (SQLiteResult.DONE != statement.Step())
                {
                    tags.Add((String)statement[0]);
                }
            }
            this.InitializeComponent();
            SearchWeather();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (NewTag.Text == "")
            {
                return;
            }
            else
            {
                if (!tags.Contains(NewTag.Text))
                {
                    var db = App.conn;
                    using (var statement = db.Prepare("INSERT INTO Tags (Name) VALUES (?)"))
                    {
                        statement.Bind(1, NewTag.Text);
                        statement.Step();
                    }
                    tags.Add(NewTag.Text);
                    Tags.SelectedIndex = tags.Count - 1;
                }
                NewTag.Text = "";

            }
        }

        
        ///<summary>
        ///查询天气
        ///</summary>

        private void SearchWeather()
        {
            /*(var accessStatus = await Geolocator.RequestAccessAsync();
            if (accessStatus != GeolocationAccessStatus.Allowed)
                throw new Exception();
            var geolocator = new Geolocator { DesiredAccuracyInMeters = 0 };
            var position = await geolocator.GetGeopositionAsync();
            double lat = position.Coordinate.Point.Position.Latitude;
            double lon = position.Coordinate.Point.Position.Longitude;

            string latlng = lat.ToString() + lon.ToString();
            string url = "http://apis.juhe.cn/geo/?key=cf993e0a9515499caeaa87b7e04ca57e&lat=" + lat.ToString() + "&lng="+ lon.ToString() +"&type=1";
            HttpClient client = new HttpClient();
            string result = await client.GetStringAsync(url);
            JsonReader reader = new JsonTextReader(new StringReader(result));*/
            string cityname = "广州";
           /* while (reader.Read())
            {
                if ((String)reader.Value == "")
                    throw new Exception();
                if((String)reader.Value == "city")
                {
                    reader.Read();
                    cityname = (String)reader.Value;
                    break;
                }
            }*/
            queryAsync(cityname);
        }

        async void queryAsync(string cityname)
        {
            string appkey = "58d7af028a82d45843d2905dbe10fcbd";
            string url = "http://v.juhe.cn/weather/index?format=2&cityname=" + cityname + "&key=" + appkey;
            HttpClient client = new HttpClient();
            string result = await client.GetStringAsync(url);
            JsonReader reader = new JsonTextReader(new StringReader(result));
            int count = 0;
            string weatherID = "";
            string weather = "";
            while (reader.Read())
            {
                if ((String)reader.Value == "")
                    throw new Exception();
                if ((String)reader.Value == "weather")
                {
                    reader.Read();
                    weather = (String)reader.Value;
                    count += 1;
                }
                if ((String)reader.Value == "temperature")
                {
                    reader.Read();
                    weather = weather + (String)reader.Value;
                    count += 1;
                }
                if ((String)reader.Value == "fa")
                {
                    reader.Read();
                    weatherID = (String)reader.Value;
                    icon.Source = new BitmapImage(new Uri("ms-appx:///Assets/" + weatherID + ".png"));
                    count += 1;
                }
                if (count == 3)
                {
                    break;
                }
            }
        }

        ///<summary>
        ///获取音乐
        ///</summary>

        private async void chose_Click(object sender, RoutedEventArgs e)
        {
            await SetLocalMedia();
        }

        async private System.Threading.Tasks.Task SetLocalMedia()
        {
            var openPicker = new Windows.Storage.Pickers.FileOpenPicker();

            openPicker.FileTypeFilter.Add(".wma");
            openPicker.FileTypeFilter.Add(".mp3");

            var file = await openPicker.PickSingleFileAsync();

            // mediaPlayer is a MediaPlayerElement defined in XAML
            if (file != null)
            {
                var stream = await file.OpenAsync(Windows.Storage.FileAccessMode.Read);
                slider.Visibility = Windows.UI.Xaml.Visibility.Visible;
                mediaCommand.Visibility = Windows.UI.Xaml.Visibility.Visible;
                mediaPlayer.SetSource(stream, file.ContentType);
                mediaPlayer.Play();
            }
        }

        private void pause_Click(object sender, RoutedEventArgs e)
        {
            mediaPlayer.Pause();
        }

        private void play_Click(object sender, RoutedEventArgs e)
        {
            mediaPlayer.Play();
        }

        private void stop_Click(object sender, RoutedEventArgs e)
        {
            mediaPlayer.Stop();
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

        private void Volume_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            mediaPlayer.Volume = Volume.Value / 100;
        }

        DispatcherTimer timer = null;

        private void slider_ValueChanged(object sender, RangeBaseValueChangedEventArgs e)
        {
            mediaPlayer.Position = TimeSpan.FromSeconds(slider.Value);
        }

        private void mediaPlayer_MediaOpened(object sender, RoutedEventArgs e)
        {
            slider.Maximum = mediaPlayer.NaturalDuration.TimeSpan.TotalSeconds;
            //媒体文件打开成功
            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(1);
            timer.Tick += Timer_Tick;
            timer.Start();
        }

        private void Timer_Tick(object sender, object e)
        {
            slider.Value = mediaPlayer.Position.TotalSeconds;
        }

        /// <summary>
        /// 获取图片
        /// </summary>

        private void openFile(object sender, RoutedEventArgs e)
        {
            //需要给一个放图片的地址……
            selecPic(pic);
        }

        public async void selecPic(Image pic)
        {
            var fop = new FileOpenPicker();
            fop.ViewMode = PickerViewMode.Thumbnail;
            fop.SuggestedStartLocation = PickerLocationId.PicturesLibrary;
            fop.FileTypeFilter.Add(".jpg");
            fop.FileTypeFilter.Add(".png");
            fop.FileTypeFilter.Add(".png");
            fop.FileTypeFilter.Add(".gif");

            StorageFile file = await fop.PickSingleFileAsync();
            try
            {
                using (IRandomAccessStream fileStream = await file.OpenAsync(FileAccessMode.Read))
                {
                    BitmapImage bitmapImage = new BitmapImage();
                    await bitmapImage.SetSourceAsync(fileStream);
                    pic.Source = bitmapImage;
                }
            }
            catch (Exception)
            {
                return;
            }
        }

        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            ListItem item = App.item;
            create = true;
            if (item != null)
            {
                create = false;
                title.Text = item.title;
                detail.Text = item.description;
                Date.Date = item.date;
                Tags.SelectedValue = item.tag;
                ID = GetId();
                lastdate = item.date;
                App.item = null;
            }
            if(App.selectTimeFlag == true)
            {
                Date.Date = App.selectTime;
                App.selectTimeFlag = false;
            }
        }


        private void AddAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            string Title = title.Text;
            string des = detail.Text;
            string tag = Tags.SelectedValue.ToString();
            string date = Date.Date.ToString();
            string sql = "insert into Items (Title, Details, Date, Tag) values (?, ?, ?, ?)";
            if(!create)
            {
                sql = "UPDATE Items SET Title = ?, Details = ?, Date = ?, Tag = ? WHERE Id = ?";
            }
            using (var cust_stmt = App.conn.Prepare(sql))
            {

                cust_stmt.Bind(1, Title);
                cust_stmt.Bind(2, des);
                cust_stmt.Bind(3, date);
                cust_stmt.Bind(4, tag);
                if (!create)
                {
                    cust_stmt.Bind(5, ID);
                }
                cust_stmt.Step();
            }
            Frame rootFrame = Window.Current.Content as Frame;
            rootFrame.GoBack();
            Update(Title, date);
        }
        private int GetId()
        {
            int id = 0;
            string vtitle = App.item.title;
            string vdetails = App.item.description;
            using (var statement = App.conn.Prepare("select * from Items"))
            {
                while (statement.Step() != SQLiteResult.DONE)
                {
                    string did = statement[0].ToString();
                    string dtitle = statement[1].ToString();
                    string ddetails = statement[2].ToString();
                    if (vtitle == dtitle && vdetails == ddetails)
                    {
                        id = int.Parse(did);
                        break;
                    }
                }
            }
            return id;
        }

        private void Date_DateChanged(object sender, DatePickerValueChangedEventArgs e)
        {
            
            if (DateTime.Compare(new DateTime(Date.Date.Year, Date.Date.Month, Date.Date.Day), new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day)) > 0)
            {
                Date.Date = lastdate;
                return;
            }
            create = true;
            string date = "%"+ Date.Date.Year.ToString() + '/' + Date.Date.Month.ToString() + '/' + Date.Date.Day.ToString() + "%";
            using (var statement = App.conn.Prepare("select * from Items WHERE Date LIKE ?"))
            {
                statement.Bind(1, date);
                while (statement.Step() != SQLiteResult.DONE)
                {
                    ID = int.Parse(statement[0].ToString());
                    title.Text = statement[1].ToString();
                    detail.Text = statement[2].ToString();
                    Tags.SelectedValue = statement[3].ToString();
                    create = false;
                }
            }
            if (create)
            {
                title.Text = "";
                detail.Text = "";
                Tags.SelectedIndex = 0;
            }
        }

        private void DeleteAppBarButton_Click(object sender, RoutedEventArgs e)
        {
            var db = App.conn;
            string date = "%" + Date.Date.Year.ToString() + "/" + Date.Date.Month.ToString() + "/" + Date.Date.Day.ToString() + "%";
            string sql = @"DELETE FROM Items WHERE Date like ?";
            using (var res = db.Prepare(sql))
            {
                res.Bind(1, date);
                res.Step();
            }
          

            Frame.Navigate(typeof(MainPage));

        }

        /// <summary>
        /// 更新磁贴
        /// </summary>
        private void Update(string title, string date) {
            TileUpdater updater = TileUpdateManager.CreateTileUpdaterForApplication();
            XmlDocument xml = new XmlDocument();
            xml.LoadXml(File.ReadAllText("Tile.xml"));
            XmlNodeList texts = xml.GetElementsByTagName("text");
            XmlNodeList images = xml.GetElementsByTagName("image");
            foreach (IXmlNode text in texts) {
                if (text.InnerText == "Title")
                    text.InnerText = title;
                if (text.InnerText == "Date")
                    text.InnerText = date;
            }
            var notification = new TileNotification(xml);
            updater.EnableNotificationQueue(true);
            updater.Update(notification);
        }
    }
}
