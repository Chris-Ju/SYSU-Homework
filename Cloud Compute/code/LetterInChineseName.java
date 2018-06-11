import java.io.IOException;
import java.util.StringTokenizer;
 
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;
 

public class LetterInChineseName {

  public static void main(String[] args) throws Exception {
    if (args.length != 2) {
      System.err.println("Usage: LetterInChineseName <input path> <output path>");
      System.exit(-1);
    }

    // 设置jar包及作业名称
    Job job = new Job();
    job.setJarByClass(LetterInChineseName.class);
    job.setJobName("Letter In Chinese Name");

    // 输入输出路径
    FileInputFormat.addInputPath(job, new Path(args[0]));
    FileOutputFormat.setOutputPath(job, new Path(args[1]));

    // 设置Mapper和Reducer实现
    job.setMapperClass(LetterInChineseNameMapper.class);
    job.setReducerClass(LetterInChineseNameReducer.class);

    // 设置输出格式
    job.setOutputKeyClass(Text.class);
    job.setOutputValueClass(IntWritable.class);

    // 等待作业完成后退出
    System.exit(job.waitForCompletion(true) ? 0 : 1);
  }
}