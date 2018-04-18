using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.UI.Xaml.Media;

namespace MyList.Models
{
    class TodoItem
    {
        public string id;
        public string title { get; set; }
        public string description { get; set; }
        public bool completed { get; set; }
        public DateTime date { get; set; }
        public ImageSource source { get; set; }
        public string picPath;
        public TodoItem(string title, string description, DateTime d, ImageSource imgSource, string picPath, bool comp)
        {
            this.id = Guid.NewGuid().ToString();
            this.title = title;
            this.description = description;
            this.completed = false;
            this.date = d;
            this.source = imgSource;
            this.picPath = picPath;
            this.completed = comp;

        }
    }
}
