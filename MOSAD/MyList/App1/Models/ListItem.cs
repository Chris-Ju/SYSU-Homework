using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Runtime.CompilerServices;
using System.Text;
using System.Threading.Tasks;
using Windows.Storage;
using Windows.UI.Xaml;
using Windows.UI.Xaml.Data;
using Windows.UI.Xaml.Media;

namespace MyList.Models
{
    class TodoItem
    {

        private string id;
        public bool completed { get; set; }
        public string GetId() { return this.id; }
        public string description { get; set; }
        public ImageSource source { get; set; }
        public string title { get; set; }
        public DateTime date { get; set; }
        public StorageFile f;
        public TodoItem(string title, string description, DateTime date, ImageSource source, StorageFile f)
        {
            this.id = Guid.NewGuid().ToString(); //生成id
            this.title = title;
            this.description = description;
            this.completed = false; //默认为未完成
            this.date = date;
            this.source = source;
            this.f = f;
        }

      
    }
}
