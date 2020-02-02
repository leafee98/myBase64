# myBase64

个人实现的一个Base64编解码轮子

## 使用

### 生成静态链接库

使用命令行则是与配置好的`task`相同的效果, 终归`task`也只是命令行的一种便捷方式罢了, 具体命令如下:

```
mkdir -p ./out
g++ -c ./src/myBase64.cpp -o ./out/myBase64.o
ar -r ./out/libmyBase64.a ./out/myBase64.o
```

另外可以使用`make`来构建, 效果和命令行构建是一样的, 或者说是只不过是把命令行的命令照搬进`makefile`里面了.

```
make all
```

### 在其他项目中使用

把此项目中的`myBase64.h`头文件和生成的`libmyBase64.a`拷走, 包含在你自己的项目中, 然后在编译的时候使用以下命令即可编译.

其中`lib`是静态链接库的目录, `myBase64`是生成的静态链接库(默认指定静态链接库名称后, 编译器会在名称前加上`lib`, 在加上后缀`.a`后寻找静态链接库文件)

```
# 注意静态链接库的参数要放在最后面
g++ {your cpp files} -Llib -lmyBase64
```

## 注意事项

目前仅支持字符串编解码, 同时并未处理文本编码, 所以在对如汉字等非ASCII码的字符串编码时, 在不同的系统中有可能会出现与通用编解码不同的结果.

## 基于注意事项的建议

1. 尽可能编解码英文
2. 不要解码太长的东西

## 许可证

1. 可随意使用, 不限制使用范围.
2. 可不署名原作者(好挫的代码署名丢人`＞﹏＜`)
3. 造成的一切后果与原作者无关.
