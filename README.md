### Toy 语言的 LR(1) 语法分析器

**1. 项目架构**

采用 LR(1) 语法分析技术，解析输入的语法文件构造 LR(1) 项目集规范族、LR(1) 分析表（包括 Action 表和 Goto 表），再利用 LR(1) 分析表对输入的源文件分解出的 Token 流做移进-规约分析，最终生成语法树。

项目采用模块化设计，对每个模块都设置了单元测试，可以采用如下方式进行全模块测试：

**2. 测试方式**：

进入 `src` 目录下，使用 `bash` 运行

```
sh runTests.sh
```

对于各个模块都有单元测试，运行结果类似下图，通过全部词法、语法分析，LL(1) 分析和 LR(1) 分析生成的语法树结构也完全一致。

<img src="./1.png" alt="1" style="zoom:50%;" />

**3. 构建方式**：

进入 `src` 目录下，使用 `bash` 运行

```
sh build.sh
```

生成 `parser.exe`。

**4. 运行方式**：

进入 `bin` 目录下，命令行运行（注意语法文件必须指定 `Toy_LR1.grammar`，LL(1) 用的语法和 LR(1) 用 的语法不同，前者消除了左递归和公共前缀，后者则为了分析方便消除了空产生式）

```
./parser Toy_LR1.grammar test_0X.toy
```

第一步，程序对定义 Toy 语法的文件进行分析，生成 LR(1) 项目集规范族（`Toy_LR1_LR1States.txt`）、LR(1) 分析表（`Toy_LR1_LR1Table.csv`，包含 ACTION 表和 GOTO 表）。若源文件符合 Toy 语言的语法规则，则又会生成语法树（`test_0X_LR1.xml`）。以上 $X = 0$，$1$，$2$。

**5. 样例结果：**

`test_00.toy` 代码如下：

```
var a;
var b;
a = (1 * 2) + (3 * 4);
b = (1 * 4) + (2 * 3);
if (a > b) {
    print "(1 * 2) + (3 * 4) > (1 * 4) + (2 * 3)";
}
if (a == b) {
    print "(1 * 2) + (3 * 4) == (1 * 4) + (2 * 3)";
}
if (a < b) {
    print "(1 * 2) + (3 * 4) < (1 * 4) + (2 * 3)";
}
```

`test_00_LR1.xml` 生成语法树如下：

```xml
<?xml version="1.0" encoding="utf-8" ?>
<PROGRAM>
    <STATEMENT>
        <DECLARATION_STMT>
            <var>var</var>
            <identifier>a</identifier>
            <semicolon>;</semicolon>
        </DECLARATION_STMT>
    </STATEMENT>
    <PROGRAM>
        <STATEMENT>
            <DECLARATION_STMT>
                <var>var</var>
                <identifier>b</identifier>
                <semicolon>;</semicolon>
            </DECLARATION_STMT>
        </STATEMENT>
        <PROGRAM>
            <STATEMENT>
                <ASSIGNMENT_STMT>
                    <identifier>a</identifier>
                    <assign>=</assign>
                    <EXPRESSION>
                        <TERM>
                            <FACTOR>
                                <lparen>(</lparen>
                                <EXPRESSION>
                                    <TERM>
                                        <FACTOR>
                                            <number>1</number>
                                        </FACTOR>
                                        <TERM_SUFFIX>
                                            <multiply>*</multiply>
                                            <FACTOR>
                                                <number>2</number>
                                            </FACTOR>
                                        </TERM_SUFFIX>
                                    </TERM>
                                </EXPRESSION>
                                <rparen>)</rparen>
                            </FACTOR>
                        </TERM>
                        <EXPRESSION_SUFFIX>
                            <plus>+</plus>
                            <TERM>
                                <FACTOR>
                                    <lparen>(</lparen>
                                    <EXPRESSION>
                                        <TERM>
                                            <FACTOR>
                                                <number>3</number>
                                            </FACTOR>
                                            <TERM_SUFFIX>
                                                <multiply>*</multiply>
                                                <FACTOR>
                                                    <number>4</number>
                                                </FACTOR>
                                            </TERM_SUFFIX>
                                        </TERM>
                                    </EXPRESSION>
                                    <rparen>)</rparen>
                                </FACTOR>
                            </TERM>
                        </EXPRESSION_SUFFIX>
                    </EXPRESSION>
                    <semicolon>;</semicolon>
                </ASSIGNMENT_STMT>
            </STATEMENT>
            <PROGRAM>
                <STATEMENT>
                    <ASSIGNMENT_STMT>
                        <identifier>b</identifier>
                        <assign>=</assign>
                        <EXPRESSION>
                            <TERM>
                                <FACTOR>
                                    <lparen>(</lparen>
                                    <EXPRESSION>
                                        <TERM>
                                            <FACTOR>
                                                <number>1</number>
                                            </FACTOR>
                                            <TERM_SUFFIX>
                                                <multiply>*</multiply>
                                                <FACTOR>
                                                    <number>4</number>
                                                </FACTOR>
                                            </TERM_SUFFIX>
                                        </TERM>
                                    </EXPRESSION>
                                    <rparen>)</rparen>
                                </FACTOR>
                            </TERM>
                            <EXPRESSION_SUFFIX>
                                <plus>+</plus>
                                <TERM>
                                    <FACTOR>
                                        <lparen>(</lparen>
                                        <EXPRESSION>
                                            <TERM>
                                                <FACTOR>
                                                    <number>2</number>
                                                </FACTOR>
                                                <TERM_SUFFIX>
                                                    <multiply>*</multiply>
                                                    <FACTOR>
                                                        <number>3</number>
                                                    </FACTOR>
                                                </TERM_SUFFIX>
                                            </TERM>
                                        </EXPRESSION>
                                        <rparen>)</rparen>
                                    </FACTOR>
                                </TERM>
                            </EXPRESSION_SUFFIX>
                        </EXPRESSION>
                        <semicolon>;</semicolon>
                    </ASSIGNMENT_STMT>
                </STATEMENT>
                <PROGRAM>
                    <STATEMENT>
                        <IF_STMT>
                            <if>if</if>
                            <lparen>(</lparen>
                            <CONDITION>
                                <EXPRESSION>
                                    <TERM>
                                        <FACTOR>
                                            <identifier>a</identifier>
                                        </FACTOR>
                                    </TERM>
                                </EXPRESSION>
                                <CONDITION_SUFFIX>
                                    <greater>&gt;</greater>
                                    <EXPRESSION>
                                        <TERM>
                                            <FACTOR>
                                                <identifier>b</identifier>
                                            </FACTOR>
                                        </TERM>
                                    </EXPRESSION>
                                </CONDITION_SUFFIX>
                            </CONDITION>
                            <rparen>)</rparen>
                            <lbrace>{</lbrace>
                            <PROGRAM>
                                <STATEMENT>
                                    <PRINT_STMT>
                                        <print>print</print>
                                        <PRINT_SUFFIX>
                                            <string_literal>"(1 * 2) + (3 * 4) > (1 * 4) + (2 * 3)"</string_literal>
                                            <semicolon>;</semicolon>
                                        </PRINT_SUFFIX>
                                    </PRINT_STMT>
                                </STATEMENT>
                            </PROGRAM>
                            <rbrace>}</rbrace>
                        </IF_STMT>
                    </STATEMENT>
                    <PROGRAM>
                        <STATEMENT>
                            <IF_STMT>
                                <if>if</if>
                                <lparen>(</lparen>
                                <CONDITION>
                                    <EXPRESSION>
                                        <TERM>
                                            <FACTOR>
                                                <identifier>a</identifier>
                                            </FACTOR>
                                        </TERM>
                                    </EXPRESSION>
                                    <CONDITION_SUFFIX>
                                        <equal>==</equal>
                                        <EXPRESSION>
                                            <TERM>
                                                <FACTOR>
                                                    <identifier>b</identifier>
                                                </FACTOR>
                                            </TERM>
                                        </EXPRESSION>
                                    </CONDITION_SUFFIX>
                                </CONDITION>
                                <rparen>)</rparen>
                                <lbrace>{</lbrace>
                                <PROGRAM>
                                    <STATEMENT>
                                        <PRINT_STMT>
                                            <print>print</print>
                                            <PRINT_SUFFIX>
                                                <string_literal>"(1 * 2) + (3 * 4) == (1 * 4) + (2 * 3)"</string_literal>
                                                <semicolon>;</semicolon>
                                            </PRINT_SUFFIX>
                                        </PRINT_STMT>
                                    </STATEMENT>
                                </PROGRAM>
                                <rbrace>}</rbrace>
                            </IF_STMT>
                        </STATEMENT>
                        <PROGRAM>
                            <STATEMENT>
                                <IF_STMT>
                                    <if>if</if>
                                    <lparen>(</lparen>
                                    <CONDITION>
                                        <EXPRESSION>
                                            <TERM>
                                                <FACTOR>
                                                    <identifier>a</identifier>
                                                </FACTOR>
                                            </TERM>
                                        </EXPRESSION>
                                        <CONDITION_SUFFIX>
                                            <less>&lt;</less>
                                            <EXPRESSION>
                                                <TERM>
                                                    <FACTOR>
                                                        <identifier>b</identifier>
                                                    </FACTOR>
                                                </TERM>
                                            </EXPRESSION>
                                        </CONDITION_SUFFIX>
                                    </CONDITION>
                                    <rparen>)</rparen>
                                    <lbrace>{</lbrace>
                                    <PROGRAM>
                                        <STATEMENT>
                                            <PRINT_STMT>
                                                <print>print</print>
                                                <PRINT_SUFFIX>
                                                    <string_literal>"(1 * 2) + (3 * 4) < (1 * 4) + (2 * 3)"</string_literal>
                                                    <semicolon>;</semicolon>
                                                </PRINT_SUFFIX>
                                            </PRINT_STMT>
                                        </STATEMENT>
                                    </PROGRAM>
                                    <rbrace>}</rbrace>
                                </IF_STMT>
                            </STATEMENT>
                        </PROGRAM>
                    </PROGRAM>
                </PROGRAM>
            </PROGRAM>
        </PROGRAM>
    </PROGRAM>
</PROGRAM>
```

`test_01.toy` 代码如下：

```
var x;
var y;
input x;
if (x > -5) {
    y = x * (x / 2 + 10);
}
print y;
print "After if, finished!";
```

`test_01_LR1.xml` 生成语法树如下：

```xml
<?xml version="1.0" encoding="utf-8" ?>
<PROGRAM>
    <STATEMENT>
        <DECLARATION_STMT>
            <var>var</var>
            <identifier>x</identifier>
            <semicolon>;</semicolon>
        </DECLARATION_STMT>
    </STATEMENT>
    <PROGRAM>
        <STATEMENT>
            <DECLARATION_STMT>
                <var>var</var>
                <identifier>y</identifier>
                <semicolon>;</semicolon>
            </DECLARATION_STMT>
        </STATEMENT>
        <PROGRAM>
            <STATEMENT>
                <INPUT_STMT>
                    <input>input</input>
                    <identifier>x</identifier>
                    <semicolon>;</semicolon>
                </INPUT_STMT>
            </STATEMENT>
            <PROGRAM>
                <STATEMENT>
                    <IF_STMT>
                        <if>if</if>
                        <lparen>(</lparen>
                        <CONDITION>
                            <EXPRESSION>
                                <TERM>
                                    <FACTOR>
                                        <identifier>x</identifier>
                                    </FACTOR>
                                </TERM>
                            </EXPRESSION>
                            <CONDITION_SUFFIX>
                                <greater>&gt;</greater>
                                <EXPRESSION>
                                    <TERM>
                                        <FACTOR>
                                            <number>-5</number>
                                        </FACTOR>
                                    </TERM>
                                </EXPRESSION>
                            </CONDITION_SUFFIX>
                        </CONDITION>
                        <rparen>)</rparen>
                        <lbrace>{</lbrace>
                        <PROGRAM>
                            <STATEMENT>
                                <ASSIGNMENT_STMT>
                                    <identifier>y</identifier>
                                    <assign>=</assign>
                                    <EXPRESSION>
                                        <TERM>
                                            <FACTOR>
                                                <identifier>x</identifier>
                                            </FACTOR>
                                            <TERM_SUFFIX>
                                                <multiply>*</multiply>
                                                <FACTOR>
                                                    <lparen>(</lparen>
                                                    <EXPRESSION>
                                                        <TERM>
                                                            <FACTOR>
                                                                <identifier>x</identifier>
                                                            </FACTOR>
                                                            <TERM_SUFFIX>
                                                                <divide>/</divide>
                                                                <FACTOR>
                                                                    <number>2</number>
                                                                </FACTOR>
                                                            </TERM_SUFFIX>
                                                        </TERM>
                                                        <EXPRESSION_SUFFIX>
                                                            <plus>+</plus>
                                                            <TERM>
                                                                <FACTOR>
                                                                    <number>10</number>
                                                                </FACTOR>
                                                            </TERM>
                                                        </EXPRESSION_SUFFIX>
                                                    </EXPRESSION>
                                                    <rparen>)</rparen>
                                                </FACTOR>
                                            </TERM_SUFFIX>
                                        </TERM>
                                    </EXPRESSION>
                                    <semicolon>;</semicolon>
                                </ASSIGNMENT_STMT>
                            </STATEMENT>
                        </PROGRAM>
                        <rbrace>}</rbrace>
                    </IF_STMT>
                </STATEMENT>
                <PROGRAM>
                    <STATEMENT>
                        <PRINT_STMT>
                            <print>print</print>
                            <PRINT_SUFFIX>
                                <identifier>y</identifier>
                                <semicolon>;</semicolon>
                            </PRINT_SUFFIX>
                        </PRINT_STMT>
                    </STATEMENT>
                    <PROGRAM>
                        <STATEMENT>
                            <PRINT_STMT>
                                <print>print</print>
                                <PRINT_SUFFIX>
                                    <string_literal>"After if, finished!"</string_literal>
                                    <semicolon>;</semicolon>
                                </PRINT_SUFFIX>
                            </PRINT_STMT>
                        </STATEMENT>
                    </PROGRAM>
                </PROGRAM>
            </PROGRAM>
        </PROGRAM>
    </PROGRAM>
</PROGRAM>
```

`test_02.toy` 代码如下：

```
var max;
var i;
var j;
max = 1000000;
i = 2;
while (i * i < max + 1) {
    j = 2;
    while (j * j < i + 1) {
        if (i - i / j == 0) {
            break = break;
        }
        j = j + 1;
    }
    print i;
    print " ";
    i = i + 1;
}
```

`test_02_LR1.xml` 生成语法树如下：

```xml
<?xml version="1.0" encoding="utf-8" ?>
<PROGRAM>
    <STATEMENT>
        <DECLARATION_STMT>
            <var>var</var>
            <identifier>max</identifier>
            <semicolon>;</semicolon>
        </DECLARATION_STMT>
    </STATEMENT>
    <PROGRAM>
        <STATEMENT>
            <DECLARATION_STMT>
                <var>var</var>
                <identifier>i</identifier>
                <semicolon>;</semicolon>
            </DECLARATION_STMT>
        </STATEMENT>
        <PROGRAM>
            <STATEMENT>
                <DECLARATION_STMT>
                    <var>var</var>
                    <identifier>j</identifier>
                    <semicolon>;</semicolon>
                </DECLARATION_STMT>
            </STATEMENT>
            <PROGRAM>
                <STATEMENT>
                    <ASSIGNMENT_STMT>
                        <identifier>max</identifier>
                        <assign>=</assign>
                        <EXPRESSION>
                            <TERM>
                                <FACTOR>
                                    <number>1000000</number>
                                </FACTOR>
                            </TERM>
                        </EXPRESSION>
                        <semicolon>;</semicolon>
                    </ASSIGNMENT_STMT>
                </STATEMENT>
                <PROGRAM>
                    <STATEMENT>
                        <ASSIGNMENT_STMT>
                            <identifier>i</identifier>
                            <assign>=</assign>
                            <EXPRESSION>
                                <TERM>
                                    <FACTOR>
                                        <number>2</number>
                                    </FACTOR>
                                </TERM>
                            </EXPRESSION>
                            <semicolon>;</semicolon>
                        </ASSIGNMENT_STMT>
                    </STATEMENT>
                    <PROGRAM>
                        <STATEMENT>
                            <WHILE_STMT>
                                <while>while</while>
                                <lparen>(</lparen>
                                <CONDITION>
                                    <EXPRESSION>
                                        <TERM>
                                            <FACTOR>
                                                <identifier>i</identifier>
                                            </FACTOR>
                                            <TERM_SUFFIX>
                                                <multiply>*</multiply>
                                                <FACTOR>
                                                    <identifier>i</identifier>
                                                </FACTOR>
                                            </TERM_SUFFIX>
                                        </TERM>
                                    </EXPRESSION>
                                    <CONDITION_SUFFIX>
                                        <less>&lt;</less>
                                        <EXPRESSION>
                                            <TERM>
                                                <FACTOR>
                                                    <identifier>max</identifier>
                                                </FACTOR>
                                            </TERM>
                                            <EXPRESSION_SUFFIX>
                                                <plus>+</plus>
                                                <TERM>
                                                    <FACTOR>
                                                        <number>1</number>
                                                    </FACTOR>
                                                </TERM>
                                            </EXPRESSION_SUFFIX>
                                        </EXPRESSION>
                                    </CONDITION_SUFFIX>
                                </CONDITION>
                                <rparen>)</rparen>
                                <lbrace>{</lbrace>
                                <PROGRAM>
                                    <STATEMENT>
                                        <ASSIGNMENT_STMT>
                                            <identifier>j</identifier>
                                            <assign>=</assign>
                                            <EXPRESSION>
                                                <TERM>
                                                    <FACTOR>
                                                        <number>2</number>
                                                    </FACTOR>
                                                </TERM>
                                            </EXPRESSION>
                                            <semicolon>;</semicolon>
                                        </ASSIGNMENT_STMT>
                                    </STATEMENT>
                                    <PROGRAM>
                                        <STATEMENT>
                                            <WHILE_STMT>
                                                <while>while</while>
                                                <lparen>(</lparen>
                                                <CONDITION>
                                                    <EXPRESSION>
                                                        <TERM>
                                                            <FACTOR>
                                                                <identifier>j</identifier>
                                                            </FACTOR>
                                                            <TERM_SUFFIX>
                                                                <multiply>*</multiply>
                                                                <FACTOR>
                                                                    <identifier>j</identifier>
                                                                </FACTOR>
                                                            </TERM_SUFFIX>
                                                        </TERM>
                                                    </EXPRESSION>
                                                    <CONDITION_SUFFIX>
                                                        <less>&lt;</less>
                                                        <EXPRESSION>
                                                            <TERM>
                                                                <FACTOR>
                                                                    <identifier>i</identifier>
                                                                </FACTOR>
                                                            </TERM>
                                                            <EXPRESSION_SUFFIX>
                                                                <plus>+</plus>
                                                                <TERM>
                                                                    <FACTOR>
                                                                        <number>1</number>
                                                                    </FACTOR>
                                                                </TERM>
                                                            </EXPRESSION_SUFFIX>
                                                        </EXPRESSION>
                                                    </CONDITION_SUFFIX>
                                                </CONDITION>
                                                <rparen>)</rparen>
                                                <lbrace>{</lbrace>
                                                <PROGRAM>
                                                    <STATEMENT>
                                                        <IF_STMT>
                                                            <if>if</if>
                                                            <lparen>(</lparen>
                                                            <CONDITION>
                                                                <EXPRESSION>
                                                                    <TERM>
                                                                        <FACTOR>
                                                                            <identifier>i</identifier>
                                                                        </FACTOR>
                                                                    </TERM>
                                                                    <EXPRESSION_SUFFIX>
                                                                        <minus>-</minus>
                                                                        <TERM>
                                                                            <FACTOR>
                                                                                <identifier>i</identifier>
                                                                            </FACTOR>
                                                                            <TERM_SUFFIX>
                                                                                <divide>/</divide>
                                                                                <FACTOR>
                                                                                    <identifier>j</identifier>
                                                                                </FACTOR>
                                                                            </TERM_SUFFIX>
                                                                        </TERM>
                                                                    </EXPRESSION_SUFFIX>
                                                                </EXPRESSION>
                                                                <CONDITION_SUFFIX>
                                                                    <equal>==</equal>
                                                                    <EXPRESSION>
                                                                        <TERM>
                                                                            <FACTOR>
                                                                                <number>0</number>
                                                                            </FACTOR>
                                                                        </TERM>
                                                                    </EXPRESSION>
                                                                </CONDITION_SUFFIX>
                                                            </CONDITION>
                                                            <rparen>)</rparen>
                                                            <lbrace>{</lbrace>
                                                            <PROGRAM>
                                                                <STATEMENT>
                                                                    <ASSIGNMENT_STMT>
                                                                        <identifier>break</identifier>
                                                                        <assign>=</assign>
                                                                        <EXPRESSION>
                                                                            <TERM>
                                                                                <FACTOR>
                                                                                    <identifier>break</identifier>
                                                                                </FACTOR>
                                                                            </TERM>
                                                                        </EXPRESSION>
                                                                        <semicolon>;</semicolon>
                                                                    </ASSIGNMENT_STMT>
                                                                </STATEMENT>
                                                            </PROGRAM>
                                                            <rbrace>}</rbrace>
                                                        </IF_STMT>
                                                    </STATEMENT>
                                                    <PROGRAM>
                                                        <STATEMENT>
                                                            <ASSIGNMENT_STMT>
                                                                <identifier>j</identifier>
                                                                <assign>=</assign>
                                                                <EXPRESSION>
                                                                    <TERM>
                                                                        <FACTOR>
                                                                            <identifier>j</identifier>
                                                                        </FACTOR>
                                                                    </TERM>
                                                                    <EXPRESSION_SUFFIX>
                                                                        <plus>+</plus>
                                                                        <TERM>
                                                                            <FACTOR>
                                                                                <number>1</number>
                                                                            </FACTOR>
                                                                        </TERM>
                                                                    </EXPRESSION_SUFFIX>
                                                                </EXPRESSION>
                                                                <semicolon>;</semicolon>
                                                            </ASSIGNMENT_STMT>
                                                        </STATEMENT>
                                                    </PROGRAM>
                                                </PROGRAM>
                                                <rbrace>}</rbrace>
                                            </WHILE_STMT>
                                        </STATEMENT>
                                        <PROGRAM>
                                            <STATEMENT>
                                                <PRINT_STMT>
                                                    <print>print</print>
                                                    <PRINT_SUFFIX>
                                                        <identifier>i</identifier>
                                                        <semicolon>;</semicolon>
                                                    </PRINT_SUFFIX>
                                                </PRINT_STMT>
                                            </STATEMENT>
                                            <PROGRAM>
                                                <STATEMENT>
                                                    <PRINT_STMT>
                                                        <print>print</print>
                                                        <PRINT_SUFFIX>
                                                            <string_literal>" "</string_literal>
                                                            <semicolon>;</semicolon>
                                                        </PRINT_SUFFIX>
                                                    </PRINT_STMT>
                                                </STATEMENT>
                                                <PROGRAM>
                                                    <STATEMENT>
                                                        <ASSIGNMENT_STMT>
                                                            <identifier>i</identifier>
                                                            <assign>=</assign>
                                                            <EXPRESSION>
                                                                <TERM>
                                                                    <FACTOR>
                                                                        <identifier>i</identifier>
                                                                    </FACTOR>
                                                                </TERM>
                                                                <EXPRESSION_SUFFIX>
                                                                    <plus>+</plus>
                                                                    <TERM>
                                                                        <FACTOR>
                                                                            <number>1</number>
                                                                        </FACTOR>
                                                                    </TERM>
                                                                </EXPRESSION_SUFFIX>
                                                            </EXPRESSION>
                                                            <semicolon>;</semicolon>
                                                        </ASSIGNMENT_STMT>
                                                    </STATEMENT>
                                                </PROGRAM>
                                            </PROGRAM>
                                        </PROGRAM>
                                    </PROGRAM>
                                </PROGRAM>
                                <rbrace>}</rbrace>
                            </WHILE_STMT>
                        </STATEMENT>
                    </PROGRAM>
                </PROGRAM>
            </PROGRAM>
        </PROGRAM>
    </PROGRAM>
</PROGRAM>
```