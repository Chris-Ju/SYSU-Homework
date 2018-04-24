using System.Net.Http;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Controls;
using Newtonsoft.Json;
using Windows.UI.Popups;
using System.Text;
using Newtonsoft.Json.Linq;
using Windows.Data.Xml.Dom;
using System.Text.RegularExpressions;

// https://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x804 上介绍了“空白页”项模板

namespace HttpRequest
{
    /// <summary>
    /// 可用于自身或导航至 Frame 内部的空白页。
    /// </summary>
    public sealed partial class MainPage : Page
    {

        
        public MainPage()
        {
            Encoding.RegisterProvider(CodePagesEncodingProvider.Instance);
            this.InitializeComponent();
        }


        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            location.Text = "";
            runner.Text = "";
            ipsite.Text = "";
            if (!Regex.IsMatch(number.Text, @"^((2[0-4]\d|25[0-5]|[01]?\d\d?)\.){3}(2[0-4]\d|25[0-5]|[01]?\d\d?)$") && !Regex.IsMatch(number.Text, @"^[a-zA-Z0-9][-a-zA-Z0-9]{0,62}(\.[a-zA-Z0-9][-a-zA-Z0-9]{0,62})+$"))
            {
                var i = new MessageDialog("输入不合法").ShowAsync();
                return;
            }
            queryAsyncPhone(number.Text);
        }

        async void queryAsyncPhone(string ip)
        {
            try
            {

                string url = "http://api.k780.com/?app=ip.get&ip=" + ip + "&appkey=33116&sign=31c6db9390065b2f0def78e073e4aebc&format=xml";
                HttpClient client = new HttpClient();
                string result = await client.GetStringAsync(url);
                XmlDocument document = new XmlDocument();
                document.LoadXml(result);
                XmlNodeList list = document.GetElementsByTagName("att");
                IXmlNode node = list.Item(0);
                location.Text = node.InnerText;
                list = document.GetElementsByTagName("operators");
                node = list.Item(0);
                runner.Text = node.InnerText;
                list = document.GetElementsByTagName("ip");
                node = list.Item(0);
                ipsite.Text = node.InnerText;
            }
            catch
            {
                var i = new MessageDialog("该ip/域名不存在或未接入网络").ShowAsync();
                return;
            }
        }

        private void Button_Click_2(object sender, RoutedEventArgs e)
        {
            weather.Text = "";
            temperature.Text = "";
            if (city.Text.Length == 0)
            {
                var i = new MessageDialog("输入不合法").ShowAsync();
                return;
            }
            queryAsyncWeather(city.Text);
        }

        async void queryAsyncWeather(string city)
        {
            string url = "https://api.seniverse.com/v3/weather/now.json?key=cxatyah5f3gf9mhm&location=" + city;
            HttpClient client = new HttpClient();
            try
            {
                string result = await client.GetStringAsync(url);
                string jsonStr = result.Substring(11, result.Length - 12);
                JArray ja = (JArray)JsonConvert.DeserializeObject(jsonStr);
                weather.Text = ja[0]["now"]["text"].ToString();
                temperature.Text = ja[0]["now"]["temperature"].ToString();
            }
            catch
            {
                var i = new MessageDialog("输入不合法").ShowAsync();
                return;
            }
        }
    }
}
