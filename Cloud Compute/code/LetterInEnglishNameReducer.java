import java.io.IOException;
import java.util.StringTokenizer;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;



public class LetterInEnglishNameReducer extends Reducer<Text, IntWritable, Text, IntWritable> {

  @Override
  // 重写 reduce 函数，计算和
  public void reduce(Text key, Iterable<IntWritable> values, Context context) throws IOException, InterruptedException {
    int result = GetSum(values);
    context.write(key, new IntWritable(result));
  }

  // 私有函数，计算和 
  private static int GetSum(Iterable<IntWritable> values) {
    int result = 0;
    for (IntWritable value : values) {
      result = result + value.get();
    }
    return result;
  }
}