import java.io.IOException;
import java.util.StringTokenizer;
import java.math.BigInteger;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.Mapper;
import org.apache.hadoop.mapreduce.Reducer;
import org.apache.hadoop.mapred.MapReduceBase;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;
import org.apache.hadoop.util.GenericOptionsParser;

public class LetterInEnglishNameMapper extends Mapper<LongWritable, Text, Text, IntWritable> {

  private int[] number = new int[26];

  @Override
  public void map(LongWritable key, Text value, Context context) throws IOException, InterruptedException {

    for (int i = 0; i < 26; i++) {
      number[i] = 0;
    }
    // 行作为输入值， key 在这里暂时不需要使用
    String line = value.toString();

    // 遍历字母
    for (int i = 0; i < line.length(); i++) {
      number[line.charAt(i) - 'a']++;
    }

    for (int i = 0; i < 26; i++) {
      String letter = String.valueOf((char) (97 + i));
      context.write(new Text(letter), new IntWritable(number[i]));
    }

  }
}