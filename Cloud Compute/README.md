# README

- Hadoop 为默认设置

```
hdfs dfs -mkdir /input/ChineseName  
hdfs dfs -mkdir /input/EnglishName
hdfs dfs -put Chinese_Name.txt /input/ChineseName/
hdfs dfs -put English_Name.txt /input/EnglishName/
```

- 已经将代码打包，直接运行即可

```
hadoop jar LetterInChineseName.jar LetterInChineseName /input/ChineseName /output/ChineseName
hadoop jar LetterInEnglishName.jar LeterInEnglishName /input/EnglishName /output/EnglishName
```

- 计算完成后，将结果保存在本地

```
hdfs dfs -cat /output/ChineseName/* >> CHINESEResult
hdfs dfs -cat /output/EnglishName/* >> ENGLISHResult
```

- 由于得到的中文数据为乱序，我将它按照从大到小顺序排序(c++完成)
