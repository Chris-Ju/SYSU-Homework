# Media

- 这周作业意味着我以后可以用自己播放器看视频了?
- 作业要求
    - 实现暂停，播放，停止等操作
    - 实现进度条，实时显示媒体的播放速度;同时，拖动进度条，可以使媒体快速前进，后退到相应的位置
    - 播放视频时，可全屏显示、退出全屏
    - UI自定

- 感觉主要困难的是进度条的绑定? 不过前面 MyList 用过绑定，感觉也还好。多了的东西就是需要自己写一个 Convert
    ```xml
    <MediaElement
        x:Name="Player"
        DoubleTapped="Player_DoubleTapped"
        AutoPlay="False"
        Source="Assets/1.mp3"
        VerticalAlignment="Center"
        HorizontalAlignment="Center"
        Height="360"
        Width="520"
        Position="{Binding Value, Converter={StaticResource PAndS}, ElementName=process,Mode=TwoWay}"
        MediaOpened="me_MediaOpened"/>
    <Slider
        Margin="12,4,12,12"
        Grid.Column="4"
        Width="300"
        x:Name="process"
        ThumbToolTipValueConverter="{StaticResource MyThumbToolTipValueConverter}"
        AllowDrop="True"/>
    ```

    ```cs
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
    ```

- 图片旋转的实现
    ```xml
    <Storyboard x:Name="InnerEllStoryboard" RepeatBehavior="Forever">
        <DoubleAnimation Duration="0:0:50" From="0" To="360"
        Storyboard.TargetProperty="(UIElement.RenderTransform).(CompositeTransform.Rotation)"
        Storyboard.TargetName="Innerellipse" />
    </Storyboard>
    ```
- 注意上面代码中的 DoubleTapped="Player_DoubleTapped" 实现了双击可以全屏
- 进度条一定要双向绑定，来实现拖动可以进行调节进度
