# MYLIST
### 引言
- 万事开头难，由于在 17 年暑假修习了组合计算的过程中学习使用过C#，18年寒假实习学习了.net框架，加上对 Html 以及 Python 模块有过一定了解，所以刚开始学习过程中不算吃力。


### 简单介绍以及环境配置
- 一个好的枪手需要趁手的枪，一个好的程序员需要趁手的开发环境，以前的我，不到迫不得已是不会去使用 Visual Studio 的，因为我觉得它太流氓了，竟然强制安装系统盘。不过当我使用了之后，觉得是真的好用啊！在学习过程中，免费版的 Visual Studio Community 完全够用了，只需去官网下载就好。
    - 下载完成之后，选择需要安装的环境，这里我使用的是 C# 开发，默认选项。
    - 所有的语言入门都是 Hello World，所有的环境也是这样。
        - 点击新建项目，这里引用课件 ppt 里的一个图片
        ![](https://github.com/Chris-Ju/Picture/blob/master/HelloWorld.png?raw=true)
        - Visual Studio 自动帮你生成好了框架，只需要往里面写代码就好了，我们来介绍一下文件的结构。
            - App.xaml : 包含了一个全局可用的ResourceDictionary 对象。为了样式化各种用户界面控件，必须在这个文件中声明样式，应用程序中的任何页面都可以自动使用这些样式
            - App.xaml.cs : 此代码隐藏文件包含了重要的应用程序事件的事件处理程序，如启动、挂起和其他一些。
            - MainPage.xaml : 应用程序加载的初始页面。
            - MainPage.xaml.cs : 默认页面的代码隐藏文件。在该文件中，可以添加代码来处理控件事件或页面导航事件。
            - Assets/ : 文件夹，存放了应用的Logo图像
            - Package.appxmanifest : 该文件包含了所有的设置和应用程序的App Store 信息。在该文件中，可以修改应用程序的显示名称，设置logo 文件，设置支持的方向，以及定义应用程序需要的功能。双击该文件打开应用程序属性配置窗口，这是对该文件进行修改的首选方式
        - 点击运行，Hello World!
### 第一周
- 对于 MyList 这个项目，一开始拿到的感觉是好简单啊，这么简单的东西我肯定会快做完，事实上，第一周的任务确实如此。
    - 第一周验收内容
        - 在MainPage上放置CheckBox和line两个控件，当CheckBox被勾选时line出现，取消勾选则line消失。
        - 新建一个NewPage 点击create按钮时，检查Title、Description是否为空，DueDate是否正确（是否大于等于当前日期）。如果不正确，弹出对话框，显示错误信息。
        - 点击Cancel按钮时，Title、Description置空，DueDate置为当前日期。
- 如果在二年级上学期选修过王青老师的 Modern Web 2.0 的话，那么这周作业简直是送的，说白了就是写一个静态的网页。不过说起来也挺凶残的，Web课大约到第四次作业才将 JavaScript 引入，这里第一周就要实现功能了。
- Visual Studio 就像是 Dreamviewer，大多数代码都可以用鼠标点出来！但是作为一个有强迫症的程序员，我当然是选择键盘敲了！当然，仅限于修改 Margin Width 这类的属性。
- 稍微有一些难度的是 CheckBox 与 Line 之间的绑定，但是我第一周通过耍赖的方法赖过去了， 在 Click 函数中判断 Line 是否为可见。(代码略)
- 记得一点，C# 组件里有 DatePicker， 别像我傻乎乎使用了 Comombox。
- 没什么好说的了，直接放代码，Ps: 善用Grid！
    ```xml
    <Button x:Name="button1" Content="Create" HorizontalAlignment="Left" Margin="0,400,0,0" VerticalAlignment="Top" Height="30" Width="80" Click="button1_Click"/>
    <TextBox x:Name="Title" HorizontalAlignment="Left" Margin="0,30,0,0" Text="" VerticalAlignment="Top" Height="20" Width="320"/>
    <TextBlock x:Name="textBlock1" HorizontalAlignment="Left" Margin="0,0,0,0" Text="Title" TextWrapping="Wrap" VerticalAlignment="Top" FontSize="16"/>
    <TextBlock x:Name="textBlock2" HorizontalAlignment="Left" Margin="0,100,0,0" Text="Details" TextWrapping="Wrap" VerticalAlignment="Top" FontSize="16"/>
    <TextBox x:Name="Detail" HorizontalAlignment="Left" Margin="0,130,0,0" Text="" VerticalAlignment="Top" Height="110" Width="320" TextWrapping="Wrap"/>
    <TextBlock x:Name="textBlock3" HorizontalAlignment="Left" Margin="0,300,0,0" Text="Due Date" TextWrapping="Wrap" VerticalAlignment="Top" FontSize="16"/>
    <Button x:Name="button2" Content="Cancel" HorizontalAlignment="Right" Margin="0,400,0,0" VerticalAlignment="Top" Height="30" Width="80" Click="button2_Click"/>
    <DatePicker x:Name="DatePicker_1" Margin="0,270,0,0" HorizontalAlignment="Center" Width="320"/>
    ```
    ```cs
    private async void button1_Click(object sender, RoutedEventArgs e)
    {
        String reason = "";
        Boolean flag = false;
        if (Title.Text == "")
        {
            reason = "Title is empty!\n";
        }
        if (Detail.Text == "")
        {
            reason += "Detail is empty!\n";
        }
        if (DateTime.Compare(new DateTime(DatePicker_1.Date.Year, DatePicker_1.Date.Month, DatePicker_1.Date.Day), new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day)) < 0)
        {
            reason += "Date is wrong!\n";
        }
        if (reason == "")
        {
            flag = true;
        }
        if (!flag)
        {
            var messageDialog = new MessageDialog(reason);
            await messageDialog.ShowAsync();
        }
        else
        {
            var messageDialog = new MessageDialog("Create successfully!");
            await messageDialog.ShowAsync();
        }
    }
    private void button2_Click(object sender, RoutedEventArgs e)
    {
        Title.Text = "";
        Detail.Text = "";
        DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
    }
    ```
### 第二周
- 第二周是悲惨的一周，上完课我就突发水痘回家了，作业是在家中写的，不过也不是很难。
    - 第二周验收内容
        - 完成MainPage、NewPage两个界面的设计
        - 结合第一周完成的逻辑部分
        - 界面要求 ：
	        - 界面宽度发生改变时，界面整体始终居中；
	        - 界面右侧需有滚动条。
	        - 尽可能使得界面简介、美观，例如为界面添加背景。
- 主要问题在于页面的跳转，以及返回符号在 MainPage 中的隐藏。
- C# 中有一个称谓 Navigated 的属性? ( 我找不到合适的形容词来形容 ) 该属性可以完成页面跳转时参数的传递等一系列事情。在博客一开始曾介绍过， App.xmal.cs 的作用，所以其实不难想到，本周作业的很大一部分是在 App.xaml.cs 里实现的。(神特么不难想到，要不是 ppt 里有，我不知道得想多久 )
    ```cs
    private void OnNavigated(object sender, NavigationEventArgs e)
    {
        SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
        ((Frame)sender).CanGoBack ?
        AppViewBackButtonVisibility.Visible :
        AppViewBackButtonVisibility.Collapsed;
    }
    ```
- 上面的函数实现了返回按钮的可见，由于 AppViewBackButtonVisibility 是框架自带的属性，所以我们不需要写控件来声明它。 sender 对象其实就是页面，属于 Frame 类， CanGoBack 是其自带的属性，我们在之后还会用到它。
    ```cs
    private void OnBackRequested(object sender, BackRequestedEventArgs e)
    {
        Frame rootFrame = Window.Current.Content as Frame;
        if (rootFrame == null) return;
        
        if(rootFrame.CanGoBack && e.Handled == false)
        {
            e.Handled = true;
            rootFrame.GoBack();
        }
    }
    ```
- 上面的函数实现了返回功能，先不讨论如何激发事件。该函数的对象名以及属性名其实已经很清晰了， e 指的返回事件。

- 很多同学会好奇，该如何把实现事件的激发呢? 对于对象，我们可以直接加上类似于 OnClick 的事件，对于 Frame 该如何实现? 其实道理是一样的。两行代码搞定！
    ```cs
    rootFrame.Navigated += OnNavigated;
    SystemNavigationManager.GetForCurrentView().BackRequested += OnBackRequested;
    ```
- 在这里解释一下，C# 是面向对象的语言，函数本身是可以添加的，这代表的是如同一个盒子，当触发事件时，执行盒子中的所有函数。

- AppAddBarButton 我觉得应该不需要去赘述许多了。需要注意的是 C# 页面跳转都是由 Navigeted 完成。( 其实此处标准应该为NewPage, 我新建类时建错了 )
    ```cs
    Frame.Navigate(typeof(App1.BlankPage1));
    ```

### 第三周
- 第三周是提交成品的时候了，我本身是非常绝望的，因为身体原因缺了一节课，对于数据绑定一脸懵逼，而且是在 DDL 前48小时开始动身，感觉被事情踹着走。
- MyList 这个项目最难实现的就是数据绑定，然而，如果理解后就会觉得其实很简单的，所谓会者不难，难者不会。
- 验收内容
    - Adaptive UI
        - 为ListView设置VisualStateGroup，使得窗口宽度小于800时，右侧布局不显示；小于600时，image不显示。
        - 在宽屏显示两列的情况下，点击 ‘+’ 不会跳转。
    - Data Binding
        - 选中某项显示详情，窄屏跳新界面，宽屏显示在右边，注意按钮与新建界面不同
        - 实现Update、Delete函数
        - 在窄屏显示一列的情况下删除或添加后要跳转到Mainpage界面
- #### 首先来介绍 Adaptive UI
    - 我觉得这是我学完三周 C# 最有意思的地方了，Blend for Visual Studio 为我们提供了很好地帮助，只需要点击状态，手动即可完成 VisualState 的实现。需要注意的是，我们可以修改的是保持该状态的最小宽度或者高度，意味着如果我们需要实现作业内容，则需要设置 0 px， 600 px， 800 px 三个档。实现代码如下：( 代码其实非常容易理解 )![](https://github.com/Chris-Ju/Picture/blob/master/VisualStateGroup.jpg?raw=true)
    ``` xml
    <VisualStateManager.VisualStateGroups>
        <VisualStateGroup x:Name="VisualStateGroup">
            <VisualState x:Name="Up800px">
                <VisualState.StateTriggers>
                    <AdaptiveTrigger MinWindowWidth="800"/>
                </VisualState.StateTriggers>
            </VisualState>
            <VisualState x:Name="Between600_800">
                <VisualState.Setters>
                    <Setter Target="Grid_2.(UIElement.Visibility)" Value="Collapsed"/>
                </VisualState.Setters>
                <VisualState.StateTriggers>
                    <AdaptiveTrigger MinWindowWidth="600"/>
                </VisualState.StateTriggers>
            </VisualState>
            <VisualState x:Name="Below600px">
                <VisualState.StateTriggers>
                    <AdaptiveTrigger MinWindowWidth="0"/>
                </VisualState.StateTriggers>
                <VisualState.Setters>
                    <Setter Target="Grid_2.(UIElement.Visibility)" Value="Collapsed"/>
                     <Setter Target="Temp_1.(UIElement.Visibility)" Value="Collapsed"/>
                </VisualState.Setters>
            </VisualState>
        </VisualStateGroup>
    </VisualStateManager.VisualStateGroups>
    ```
- ### 数据绑定
    - 我在这里卡了真的好久啊，很多东西没有理解，以及 Visual Studio 自己的抽风。
    - 首先，我们要理解一下 MVVM，全称 Model–view–viewmodel，先看一下维基的解释
        ```
        MVVM有助于将图形用户界面的开发与业务逻辑或后端逻辑（数据模型）的开发分离开来，这是通过置标语言或GUI代码实现的。MVVM的视图模型是一个值转换器，这意味着视图模型负责从模型中暴露（转换）数据对象，以便轻松管理和呈现对象。在这方面，视图模型比视图做得更多，并且处理大部分视图的显示逻辑。视图模型可以实现中介者模式，组织对视图所支持的用例集的后端逻辑的访问。
        ```
    - 这都是什么东西，能不能上个图，好的老板！
        ![](https://github.com/Chris-Ju/Picture/blob/master/MVVM.png?raw=true)
    - 我觉得通过图片其实就可以很清晰的理解这个模式了，简而言之 Model 中储存的为模板，ViewModel 中为对模板的操作，View 就是我们的 Page。
    - 先来看模板

        ```cs
        class TodoItem
        {
            public TodoItem(String title, String description, DateTime date, ImageSource source)
            {
                this.id = Guid.NewGuid().ToString();
                this.title = title;
                this.description = description;
                this.date = date;
                this.source = source;
                this.completed = false;
            }
            public String id;

            public String title { get; set; }

            public String description { get; set; }

            public Boolean completed { get; set; }

            public DateTime date { get; set; }

            public ImageSource source { get; set; }
        }
         ```

    - 初学 C# 的应该不太清楚 get 与 set 是什么 ( 其实我就不清楚 )，为此，我查了一些博客。
        - [浅析C# get set的简单用法](http://developer.51cto.com/art/200909/151051.htm)
     - 其次看对模板的操作，我觉得这里没什么好说的。
        ```cs
        private ObservableCollection<Models.TodoItem> allItems = new ObservableCollection<Models.TodoItem>();

        public ObservableCollection<Models.TodoItem> AllItems { get { return this.allItems; } }

        private Models.TodoItem selectedItem = default(Models.TodoItem);

        public Models.TodoItem SelectedItem { get { return selectedItem; } set { this.selectedItem = value; } }

        public void AddTodoItem(String title, String description, DateTime date, ImageSource source)
        {
            this.allItems.Add(new Models.TodoItem(title, description, date, source));
        }

        public void RemoveTodoItem(String id)
        {
            foreach (var item in this.allItems)
            {
                if (item.id == id)
                {
                    this.allItems.Remove(item);
                    break;
                }
            }
            this.selectedItem = null;
        }

        public void UpdateTodoItem(String id, String title, String description, DateTime date, ImageSource source)
        {
            foreach (var item in this.allItems)
            {
                if (item.id == id)
                {
                    item.title = title;
                    item.description = description;
                    item.date = date;
                    break;
                }
            }
            this.selectedItem = null;
        }
        ```

    - 数据绑定
        - xaml 里是拥有模板的，通过模板来实现数据绑定
            ```xml
             <ListView IsItemClickEnabled="True" ItemClick="ListView_ItemClick"
                  ItemsSource="{x:Bind ViewModels_1.AllItems}" >
                <ListView.ItemTemplate>
                    <DataTemplate x:DataType="md:TodoItem">
                        <Grid x:Name="Grid_1" Grid.Column="0">
                            <Grid.ColumnDefinitions>
                                <ColumnDefinition Width="30" />
                                <ColumnDefinition Width="32" />
                                <ColumnDefinition Width="Auto" />
                                <ColumnDefinition Width="*" />
                            </Grid.ColumnDefinitions>
                            <Grid.RowDefinitions>
                                <RowDefinition Height="30" />
                                <RowDefinition Height="*" />
                            </Grid.RowDefinitions>
                            <CheckBox x:Name="checkBox" Grid.Row="1" Grid.Column="1" VerticalAlignment="Center" Height="20" Width="20" />
                            <Image x:Name="image" Grid.Row="1" Grid.Column="2" Source="{x:Bind source}" Height="90" Width="90" Margin="0 0 20 20" Visibility="{Binding Visibility, ElementName=Temp_1}"/>
                            <TextBlock x:Name="textBlock" Grid.Row="1" Grid.Column="3" Text="{x:Bind title}"  VerticalAlignment="Center" Foreground="Black" FontSize="36"/>
                            <Line x:Name="Line_1" Width="250" Grid.Row="1" Grid.Column="3" Stretch="Fill" Stroke="Black" StrokeThickness="2" X1="1" VerticalAlignment="Center"  Visibility="{Binding IsChecked, ElementName=checkBox}"/>
                        </Grid>
                    </DataTemplate>
                </ListView.ItemTemplate>
            </ListView>
            ```

        - 需要注意的是，ItemSource 中的对象要在 .cs 文件里实例化。Datatype 需要using 你的model 的 namespace。**此处的 TodoItem 一直抽风显示不存在，然而点击运行后发现却可以运行?** 这句话加粗意味着我在这个地方卡了好久，我舍友卡到心态爆炸。
        - 其实理解了 MVVM 模式，该处的数据绑定就很容易理解了，通过看代码就可以明白意思。
        - 由于页面在 600px 以下时隐藏图片，但是对于模板类中的组件无法正常的通过 VisualState 隐藏，这里我借鉴了 竹林吟 大佬的方法，将该图片与模板外面的一个不可见的组件绑定，对模板外组件进行操作。
    - 之后是对 cs 文件的修改，这个就很容易了，只需要调用 ViewModel 对象的函数即可。比较困难的是实现 NewPage 与 MainPage 之间 ViewModel 的同一化，本来我想使用单例模式来完成，但是在实现过程中遇到一些困难，如果以后解决后，会更新此文。( 已更新，详情见第四周 )于是，我参考了一些实现方法，通过 Navigated 在页面之间进行传递。( 不过我真是觉得这样效率很低 )
    ```cs
    Frame.Navigate(typeof(App1.BlankPage1), ViewModels_1);
    ```

    - 需要注意的是由于 NewPage 在 Create 后需要把 ViewModel 传递回来，所以不可以使用 rootFrame.GoBack(), 需要用 Navigate 生成新的 MainPage。 这样我们需要在 MainPage 中对后退按钮进行隐藏，同时对 MainPage 的 onNavigate 进行定义

    ```cs
    protected override void OnNavigatedTo(NavigationEventArgs e)
    {
        Windows.UI.Core.SystemNavigationManager.GetForCurrentView().AppViewBackButtonVisibility =
        Windows.UI.Core.AppViewBackButtonVisibility.Collapsed;
        if (e.Parameter.GetType() == typeof(ViewModels.TodoViewModels))
        {
            this.ViewModels_1 = (ViewModels.TodoViewModels)(e.Parameter);
        }
    }
    ```

    - 解决了这个问题，基本上算是完成了，剩下只剩下一些小的修改。
- ### 后期测试
    - 我在对 App 进行测试时，发现了一个很大的问题，在 MainPage 进行 Update 操作时，List 里面的信息不会发生改变，但是点击后，显示的信息却改变了。于是，我理解到 Frame 的模板不会改变而自动刷新，所以我在 Update 后加了个 Navigate
    ```cs
    ViewModels_1.UpdateTodoItem(ViewModels_1.SelectedItem.id, Title.Text, Detail.Text, new DateTime(DatePicker_1.Date.Year, DatePicker_1.Date.Month, DatePicker_1.Date.Day), this.Image_1.Source);
    var messageDialog = new MessageDialog("Update successfully!");
    DatePicker_1.Date = new DateTime(DateTime.Now.Year, DateTime.Now.Month, DateTime.Now.Day);
    await messageDialog.ShowAsync();
    this.Frame.Navigate(typeof(MainPage), ViewModels_1);
    ```

## 第四周
- 没想到第四周左右还是完善MyList。不过这周作业比较简单，只需要实现挂起时的数据恢复，但是其中存在的问题还是值得一说的。
- 作业要求
    - Mainpage.xaml.cs）在MainPage中点击checkbox出现横线，输入数据（选择图片），挂起并关闭程序，重新启动时，程序显示在Mainpage界面，并且点击的checkbox与对应横线，数据与图片都存在。
    -（Newpage.xaml.cs）在NewPage中输入数据（或选择图片），挂起并关闭程序，重新启动时，程序显示在Newpage界面，数据与图片都存在。
- 首先，完成了单例模式，上周完成过程中理解有一些小偏差，所以导致出现了问题，其实 C# 的单例模式跟 Cpp 是一样的，只不过因为 C# 是类 Java 类语言， 所有的实现都在类里，所以在引用时需要加上命名空间，我就因为这个被卡了好久，想想这是愚蠢。

    ```cs
    ///构造
    class TodoViewModels
    {
        private static TodoViewModels Instance;
        private TodoViewModels() { }
        public static TodoViewModels GetInstance()
        {
            if(Instance == null)
            {
                Instance = new TodoViewModels();
            }
            return Instance;
        }
    }

    ///调用
    View_Model = TodoViewModels.GetInstance();
    ```
- 老师在上课过程中还讲了比单例模式更强大的 IOC Containers，我会找个时间翻译一下官方文档，到时候把地址放上来 [官方文档](https://msdn.microsoft.com/en-us/magazine/jj991965.aspx)
- 我这么懒的人，为什么要实现单例模式呢，因为我在完成作业中遇到了一个 BUG ![](https://github.com/Chris-Ju/Picture/blob/master/NavigatedBug.png?raw=true)
- 在 MainPage 进行挂起并关闭时并没有发生该错误，然而在 NewPage 中就发生了 Bug， 于是我求助了 Bob Kong， 他说这是由于我传了一个 ViewModel，但是 ViewModel 不是序列化的，所以会发生报错，这我就懵逼了...什么叫序列化? [C#的序列化与反序列化](http://www.cnblogs.com/qqflying/archive/2008/01/13/1037262.html)
- 我看完之后立刻失去了兴趣，还是去改单例吧。
- 作业代码

    - 写在 OnSuspending 函数中
    
        ```cs
        issuspend = true; // App类中的静态变量，为了判断是否挂起
        Frame frame = Window.Current.Content as Frame;
        ApplicationData.Current.LocalSettings.Values["NavigationState"] = frame.GetNavigationState(); // 将所处在的状态保存进入LocalSetting
        // ApplicationData.Current.LocalSettings : The application settings container. The name of each setting can be 255 characters in length at most. Each setting can be up to 8K bytes in size and each composite setting can be up to 64K bytes in size.
        ```

    - 写在 OnLaunch 函数中的
        ```cs
        if (e.PreviousExecutionState == ApplicationExecutionState.Terminated)
        {
            //TODO: 从之前挂起的应用程序加载状态
            if (ApplicationData.Current.LocalSettings.Values.ContainsKey("NavigationState"))
            {
                rootFrame.SetNavigationState((string)ApplicationData.Current.LocalSettings.Values["NavigationState"]);

            }
        }
        ```

    - 写在 OnRemusing 函数中的
        ```cs 
        private void OnResuming(object sender, object e)
        {
            issuspend = false;

        }
        ```
    - 在 Main.xaml.cs 中
        ```cs
        protected override void OnNavigatedFrom(NavigationEventArgs e)
        {
            bool susppending = ((App)App.Current).issuspend;
            if (susppending)
            {
                ApplicationDataCompositeValue composite = new ApplicationDataCompositeValue();
                composite["title"] = Title.Text;
                composite["detail"] = Detail.Text;
                BitmapImage myBitmapImage = Icon.Source as BitmapImage;
                //composite["imgae"] = myBitmapImage.UriSource.ToString();
                composite["date"] = Date.Date;
                composite["test1"] = View_Model.AllItems[0].completed;
                composite["test2"] = View_Model.AllItems[1].completed;
                ApplicationData.Current.LocalSettings.Values["NewPage"] = composite;
            }
        }
        protected override void OnNavigatedTo(NavigationEventArgs e)
        {
            this.View_Model = ViewModels.TodoViewModels.GetInstance();
            if (e.NavigationMode == NavigationMode.New)
            {
                ApplicationData.Current.LocalSettings.Values.Remove("NewPage");
            }
            else
            {
                if (ApplicationData.Current.LocalSettings.Values.ContainsKey("NewPage"))
                {
                    var composite = ApplicationData.Current.LocalSettings.Values["NewPage"] as ApplicationDataCompositeValue;
                    Title.Text = (string)composite["title"];
                    Detail.Text = (string)composite["detail"];
                    Date.Date = (DateTimeOffset)composite["date"];
                    View_Model.AllItems[0].completed = (bool)composite["test1"];
                    View_Model.AllItems[1].completed = (bool)composite["test2"];
                    //Icon.Source = new BitmapImage(new Uri((string)composite["image"]));
                    ApplicationData.Current.LocalSettings.Values.Remove("NewPage");
                }
            }
        }
        ```

- 由于挂起并关闭机制会清空 View_Model，所以我想讲 View_Model 传入 ApplicationData.Current.LocalSettings，然而该容器只接受已经序列化的数据，如上，我放弃了。同样的，我想将 ImageSource 序列化，同样以失败告终。由于 View_Model 不可以传递，所以我建了两个固定的 Item。
- 对于 Image 缓存问题，我尝试了各种办法，比如说以上代码中的注释部分，不成功的原因是改变图片后，我使用的 stream 流输入文件，导致该 Image 对象无 Source 属性。经过研究后，由于权限问题，并没有办法获得 stream 的 Uri。 于是得出了最简单结论， LocalState 复制图片然后获取地址。
- 还有个问题是 对于 x:bind 与 binding 的区别，会造成绑定 Completed 是出现问题，以后再做研究。

## 第五周

- 作业要求
    - ### Part 1 Live Tile
        - 要求使用标准的处理XML DOM方式创建动态磁贴
        - 要求采用Adaptive Tile （覆盖至少small、medium、wide）
        - 实现效果：要求每添加一条项目，磁贴能进行更新，并且更新的内容循环展示（1-2-3-4-5-1-2-3-4……）
    - ### Part 2 App to App Communication
        - 在MenuFlyoutItem中增加Share选项，点击后相应条目能进行共享
- Part 1
- C# 封装了修改的磁贴的函数，所以其实只需完成 Titl.xml 便可以实现！
    ```xml
    <?xml version="1.0" encoding="utf-8" ?>
    <tile>
    <visual>
        <binding template="TileSmall">
        <text hint-style="subtitle" hint-align="center">Small</text>
        <text hint-align="center">Text Field</text>
        <image src ="Assets/MyList.png" placement ="background"></image>
        </binding>

        <binding template="TileMedium">
        <text hint-style="subtitle" hint-align="center">Middle</text>
        <text hint-align="center">Text Field</text>
        <image src ="Assets/MyList.png" placement ="background"></image>
        </binding>

        <binding template="TileWide">
        <text hint-style="subtitle" hint-align="center">Wide</text>
        <text hint-align="center">Text Field</text>
        <image src ="Assets/MyList.png" placement ="background"></image>
        </binding>

        <binding template="TileLarge">
        <text hint-style="subtitle" hint-align="center">Large</text>
        <text hint-align="center">Text Field</text>
        <image src ="Assets/MyList.png" placement ="background"></image>
        </binding>
    </visual>
    </tile>
    ```
    ```cs
    XmlDocument tile = new XmlDocument();
    tile.LoadXml(File.ReadAllText("Tile.xml"));
    XmlNodeList tileText = tile.GetElementsByTagName("text");
    for (int i = 0; i < tileText.Count; i++)
    {
        ((XmlElement)tileText[i]).InnerText = View_Model.AllItems[View_Model.AllItems.Count - 1].title;
        i++;
        ((XmlElement)tileText[i]).InnerText = View_Model.AllItems[View_Model.AllItems.Count - 1].description;

    }
    TileNotification notification = new TileNotification(tile);
    var updator = TileUpdateManager.CreateTileUpdaterForApplication();
    updator.Update(notification);
    TileUpdateManager.CreateTileUpdaterForApplication().EnableNotificationQueue(true);
    ```
    ![](https://github.com/Chris-Ju/Picture/blob/master/TileUpdateManager.jpg?raw=true)

- 这样存在的问题是，你关闭后，由于还没有设置本地数据库保存，数据清空，但是磁贴并不清空，于是我在 App.xaml.cs 的 OnLaunch 里加了这么一段，完美
    ```cs
    if (e.PreviousExecutionState == ApplicationExecutionState.ClosedByUser)
    {
        var updator = TileUpdateManager.CreateTileUpdaterForApplication();
        updator.Clear();
    }
    ```

- 并没有找到可以选择删除的方法，于是我更新后选择 Clear 然后逐条添加。

- Part 2
- 毕竟是微软的系统，毕竟 C# 也是微软的语言，封装的各种调用还是很棒的，共享只需要写一个函数。
    ```cs
    DataTransferManager.ShowShareUI();
    ```

- App 在收到请求时， 会调用 **DataTransferManager.GetForCurrentView().DataRequested**，我们需要把自己写的函数添加到此调用中
- 如果 request.Data.Properties 没有设置 Title 与 Text 的话， 会导致 无法显示共享页面，原因以后研究后再来完善。
- 由于对于图片传递的是 file, 所以将选择的图片扔到 Model 类中保存， 以便图片共享。
    ```cs
    private async void OnShareDataRequested(DataTransferManager sender, DataRequestedEventArgs args)
    {
        DataRequest request = args.Request;
        DataRequestDeferral getFile = args.Request.GetDeferral();
        request.Data.Properties.Title = View_Model.SelectedItem.title;
        request.Data.SetText(View_Model.SelectedItem.description);
        try
        {
            if (View_Model.SelectedItem.f != null)
            {
                request.Data.Properties.Thumbnail = RandomAccessStreamReference.CreateFromFile(View_Model.SelectedItem.f);
                request.Data.SetBitmap(RandomAccessStreamReference.CreateFromFile(View_Model.SelectedItem.f));
            }
            else
            {
                StorageFile imageFile = await StorageFile.GetFileFromApplicationUriAsync(new Uri("ms-appx:///Assets/Background.jpg"));
                request.Data.SetBitmap(RandomAccessStreamReference.CreateFromFile(imageFile));
            }
        }
        finally
        {
            getFile.Complete();
        }
        getFile.Complete();
    }
    ```

## 第六周

- 这周是爆炸的一周，我还这么认真的写博客我都开始佩服我自己了。这周主要是把数据用数据库存起来，数据库的安装只需在扩展中找到 SQLite 就可以，很简单。
- 这一次连接数据库可以说是在除了 wordpress 以及 sqli 后第一次在写项目中使用数据库了，说来也是惭愧。
- 所有数据库的使用都可以在编程语言中使用 sql 语句来实现的，但是这就带来的 sqli 注入的问题，虽然 c# 提供了对于 SQLite 的接口，不需要使用 sql 语句，但是本次作业因为时间以及懒的原因，我还是使用 sql 实现的。
- 借 ppt 中的一句话， c# 使用 SQLite 只需要一个四部曲:
    - 创建 SQLiteConnection
    - 利用 SQLiteConnection.prepare()执行SQL语句
    - 对参数以"映射"形式赋值
    - 解析查询结果

- 由于在一开始便加载数据库读入 Model 数据，并且数据库也是一个全局变量，所以应该将数据库创建写在 App.xaml.cs 文件中，并于程序一打开便加载。 Sql 语句就不一一解释了，数据库课程中应该有学。

    ```cs
    private void LoadDatabase()
        {
            conn = new SQLiteConnection("demo.db");
            string sql = @"create table if not exists Customer (
                            Id integer primary key autoincrement not null,
                            Title varchar(140),
                            Details varchar(140),
                            Date varchar(140),
                            ImageUrl varchar(255),
                            IsCompleted varchar(10) not null);";
            using (var statement = conn.Prepare(sql))
            {
                statement.Step();
            }
        }
    ```

- 数据库创建好了，只需要进行增删改查操作了。
    - 增加

    ```cs
    using (var cust_stmt = App.conn.Prepare("INSERT INTO Customer (Title, Details, Date, ImageUrl, IsCompleted) VALUES (?, ?, ?, ?, ?)"))
    {
        cust_stmt.Bind(1, Title.Text);
        cust_stmt.Bind(2, Detail.Text);
        cust_stmt.Bind(3, Date.Date.ToString());
        cust_stmt.Bind(4, filePath);
        cust_stmt.Bind(5, "False");
        cust_stmt.Step();
    }
    ```

    - 删除

    ```cs
    using (var statement = App.conn.Prepare("DELETE FROM Customer WHERE Id = ?"))
    {
        statement.Bind(1, GetId());
        statement.Step();
    }
    ```

    - 修改

    ```cs
    using (var cust_stmt = App.conn.Prepare("UPDATE Customer SET Title = ?, Details = ?, Date = ?, ImageUrl = ? WHERE Id = ?"))
    {
        cust_stmt.Bind(1, Title.Text);
        cust_stmt.Bind(2, Detail.Text);
        cust_stmt.Bind(3, Date.Date.ToString());
        cust_stmt.Bind(4, filePath);
        cust_stmt.Bind(5, GetId());
        cust_stmt.Step();
    }
    ```

    - 查询

    ```cs
    string q = "%" + searchText.Text + "%";
    using (var statement = App.conn.Prepare("SELECT * FROM Customer WHERE Title LIKE ? or Details LIKE ? or Date LIKE ?"))
    {
        statement.Bind(1, q);
        statement.Bind(2, q);
        statement.Bind(3, q);
        string os = "";
        while (statement.Step() != SQLiteResult.DONE)
        {
            string tid = statement[0].ToString();
            string ttitle = statement[1].ToString();
            string tdetails = statement[2].ToString();
            string tdate = statement[3].ToString();
            // string dpicpath = statement[4].ToString();
            os += "Title: " + ttitle + "; Details: " + tdetails + "; Date: " + tdate + "\n";
        }
        var i = new MessageDialog(os).ShowAsync();
    }
    ```

- 在这里，我解释一下 GetId() 函数 // 别问我为什么写出这么差劲的代码...我懒啊，这个是直接复制粘贴的...优化后的也在下面你们自己选择

    ```cs
    private int GetId()
    {
        string query = "%%";
        int id = 0;
        string vtitle = View_Model.SelectItem.title;
        string vdetails = View_Model.SelectItem.description;
        using (var statement = App.conn.Prepare("SELECT * FROM Customer WHERE Id LIKE ? OR Title LIKE ? OR Details LIKE ? OR Date LIKE ?"))
        {
            statement.Bind(1, query);
            statement.Bind(2, query);
            statement.Bind(3, query);
            statement.Bind(4, query);

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
    ```

    ```sql
    SELECT * FROM Customer WHERE Title = ? and Details = ?
    ```
- 增删改查完成后，还有一部分没有解决，便是 *是否完成* 的问题，因为 SeletedItem 在没有点击时为 null，所以我想了很多办法，只能每次点击后依次遍历了。
    
    ```cs
    private void checkBox_Click(object sender, RoutedEventArgs e)
    {
        for (int count = 0; count < View_Model.AllItems.Count; count++)
        {
            View_Model.SelectItem = View_Model.AllItems[count];
            Debug.WriteLine(View_Model.SelectItem.completed.ToString());
            using (var statement = App.conn.Prepare("UPDATE Customer SET IsCompleted = ? WHERE Id = ?"))
            {
                statement.Bind(1, View_Model.SelectItem.completed.ToString());
                statement.Bind(2, GetId());
                statement.Step();
            }
        }
        View_Model.SelectItem = null;
    }
    ```
    
- 到这里，所有的问题都已经解决了，其实这周作业还是蛮简单的，如果你不想去实现 Image 的储存的话...
- 下面，重点来了，如何存储 Image 呢?

- 或许你已经发现了，我在 github 中 Main.xmal.cs 与 NewPage.xmal.cs 中有一个 ImageStorage.StorageImageFolder 的函数， 在 ViewModels 里面有一个函数 ImageStorage.GetLoacalFolderImage，这便是图片储存的实现。

- 来看 ImageStorage 中的函数
    - GetLoacalFolderImage 实现了图片文件的读取，将已经二进制化的文件转化为 stream 并写入 BitmapImage 中

    ```cs
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
    ```

    - StorageImageFolder 实现了图片文件的二进制保存

    ```cs
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
    ```

    - ConvertIRandomAccessStreamByte 是具体实现二进制
    - GetImageFolder 在本地创建或者读取存储图片的文件
    - Md5 文件 Url 的加密
- ps. 文件共享 图片的共享在第六周修改后有 bug，该 bug 只需将 Uri 转化为 stream 便好，懒得改了。


- 对于 StringBuilder ?不知道为什么突然问这个。 StringBuilder类型在最终生成String对象之前，将不会产生任何String对象，这很好地解决了字符串操作的性能问题 [参考地址](http://blog.51cto.com/genwoxuedotnet/503333)

- LocalFolder RoamingFolder 我认为是 App 与本地的一个连接，由于 App 权限问题，所以需要一个位置来储存数据， LocalFolder 与 RoamingFolder 本地储存地址便解决了这个问题