# Simhash Server

## 简介

简单 [simhash] 包装而成的 HTTP Server ，
主要是总是有人反馈因为不懂C++所以不知道怎么使用 [simhash] ，
希望提供个 HTTP 接口用法。
所以才有了这个项目。独立成单独一个仓库的原因是不想让 [simhash] 项目太过臃肿。

如果你喜欢该项目，请 star [simhash] 而不是该项目，以助于[simhash]的传播和更好的后续改进。多谢。

## 用法

【依赖】

+ `g++ (version >= 4.1 recommended) or clang++`;

【下载】

```sh
git clone git://github.com/yanyiwu/simhash_server.git
cd keyword_server
make
#如果是MacOSX用户，请使用 make osx 。
```

【启动服务】

```
./simhash.server
```


【请求参数】
```
n int 使用TopN关键字生成hash，默认10
s string 正文内容
```

【GET】
```
curl "http://127.0.0.1:11201/?n=5&s=你好世界"

17676873585679812141
["你好:7.95788", "世界:4.36753"]
```

【POST】

```
curl -d "我是蓝翔 技工拖拉机学院手扶拖拉机专业的。" "http://127.0.0.1:11201/?n=5"

6723932022578817358
["蓝翔:11.7392", "手扶拖拉机:10.0089", "技工:9.84023", "拖拉机:8.43685", "学院:6.5068"]
```

## 客服

```
i@yanyiwu.com
```

[simhash]:http://github.com/yanyiwu/simhash
