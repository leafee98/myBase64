# myBase64

个人实现的一个Base64编解码轮子

## 使用

### 生成静态链接库

可以看到`.vscode`目录中有配置好的`task`, 如果使用`vscode`可以在项目根目录创建`/out`目录后运行`pack lib`任务.

使用命令行则是与配置好的`task`相同的效果, 终归`task`也只是命令行的一种便捷方式罢了, 具体命令如下:

```
mkdir -p ./out
g++ -c ./myBase64.cpp -o ./out/myBase64.o
ar -r ./out/libmyBase64.a ./out/myBase64.o
```

### 在其他项目中使用

把此项目中的`myBase64.h`头文件和生成的`libmyBase64.a`拷走, 包含在你自己的项目中, 然后在编译的时候使用以下命令即可编译.

其中`lib`是静态链接库的目录, `myBase64`是生成的静态链接库(默认指定静态链接库名称后, 编译器会在名称前加上`lib`, 在加上后缀`.a`后寻找静态链接库文件)

```
g++ -Llib -lmyBase64 {your cpp files}
```

## 注意事项

目前仅支持字符串编解码, 同时并未处理文本编码, 所以在对如汉字等非ASCII码的字符串编码时, 在不同的系统中有可能会出现与通用编解码不同的结果.

目前, 在编码时可以使用桶直接拿到编码字符, 在解码时, 则是简单的O(n)查询来找到编码字符对应的值, 所以在解码的效率要远低于编码, 大概相差...32倍吧...

## 基于注意事项的建议

1. 尽可能编解码英文
2. 不要解码太长的东西

## 许可证

1. 可随意使用, 不限制使用范围.
2. 可不署名原作者(好挫的代码署名丢人`＞﹏＜`)
3. 造成的一切后果与原作者无关.