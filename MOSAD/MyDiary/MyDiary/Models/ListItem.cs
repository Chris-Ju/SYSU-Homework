using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Windows.UI.Xaml.Media;
using System.Threading.Tasks;
using Windows.Storage;
using System.Collections.ObjectModel;

namespace MyDiary.Models
{
    public class ListItem
    {
        public string title { get; set; }
        public string description { get; set; }
        public DateTime date { get; set; }
        public string tag { get; set; }

        public ListItem()
        {

        }

        public ListItem(string title, string description, string tag, DateTime d)
        {
            this.title = title;
            this.description = description;
            this.date = d;
            this.tag = tag;
        }
    }
}
