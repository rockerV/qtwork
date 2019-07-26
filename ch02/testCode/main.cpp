#include <QCoreApplication>
#include <QtTest/QTest> //added new line
#include <QDebug>       //added
#include <QApplication>
#include <QTextBrowser>
#include <QByteArray>
#include <QDataStream>
#include <QTextCodec>
void Test_setNum()
{
    qDebug()<<"----------- Test_setNum --------------------";

    QString strTest;
    //to Hex string
    short numHex = 127;
    strTest.setNum(numHex, 16);
    qDebug()<<"Hex: "<<strTest;

    //to Oct string
    int numOct = 63;
    strTest.setNum(numOct, 8);
    qDebug()<<"Oct: "<<strTest;

    //to normal Dec string
    long numDec = 800;
    strTest.setNum(numDec);
    qDebug()<<"Normal: "<<strTest;

    //to float string
    float numFixed = 123.78999;
    strTest.setNum(numFixed, 'f', 3);
    qDebug()<<"Fixed: "<<strTest;

    //to scientific double string
    double numScientific = 456.78999;
    strTest.setNum(numScientific, 'e', 6);
    qDebug()<<"Scientific: "<<strTest;
}

void Test_arg()
{
    qDebug()<<"----------- Test_arg --------------------";

    //使用 strResult 存储 arg 返回的新对象
    QString strResult;

    //Dec
    long numDec = 800;
    QString strMod = QObject::tr("Normal: %1");
    strResult = strMod.arg(numDec);  //%1是占位符，第一个arg函数参数变量转后的字符串填充到 %1 位置
    qDebug()<<"Mod: "<<strMod<<" \t Result: "<<strResult;

    //Oct
    int numOct = 63;
    strResult = QObject::tr("Oct: %1").arg(numOct, 4, 8, QChar('0'));  //numOct转换后为4字符域宽，8进制，填充0
    qDebug()<<strResult;

    //Hex
    short numHex = 127;
    QString strPrefix = QObject::tr("0x");
    //占位符里可填充数值转的字符串，也可以直接填充原有的字符串
    strResult = QObject::tr("Hex: %1%2").arg(strPrefix).arg(numHex, 0, 16);  //串联：第一个arg函数参数填充到%1，第二个arg填充到%2
    qDebug()<<strResult;

    //double
    double numReal = 123.78999;
    strResult = QObject::tr("Fixed: %1 \t Scientific: %2").arg(numReal, 0, 'f').arg(numReal, 0, 'e', 3);
    qDebug()<<strResult;

    //占位符可重复，也可乱序
    int one = 1;
    int two = 2;
    int three = 3;
    strResult = QObject::tr("%1 小于 %2，%1 小于 %3，%3 大于 %2 。").arg(one).arg(two).arg(three);
    qDebug()<<strResult;
}

void Test_toValue()
{
    qDebug()<<"----------- Test_toValue --------------------";

    bool bok = false;
    //dec
    QString strDec = QObject::tr("800");
    int nDec = strDec.toInt(&bok, 10);
    qDebug()<<nDec<<"\t"<<bok;       //成功
    //Hex
    QString strHex = QObject::tr("FFFF");
    nDec = strHex.toInt(&bok, 10);  //基数错误，转换失败
    qDebug()<<nDec<<"\t"<<bok;

    short nHexShort = strHex.toShort(&bok, 16);
    qDebug()<<nHexShort<<"\t"<<bok; //FFFF正整数太大，超出范围，转换失败，没有负号 - 的都算正数。

    ushort nHexUShort = strHex.toUShort(&bok, 16);
    qDebug()<<nHexUShort<<"\t"<<bok;//成功

    //自动转换
    QString strOct = QObject::tr("0077");
    int nOct = strOct.toInt(&bok, 0);
    qDebug()<<nOct<<"\t"<<bok;  //字符 0 打头自动按八进制转

    QString strHexWithPre = QObject::tr("0xFFFF");
    int nHexWithPre = strHexWithPre.toInt(&bok, 0);
    qDebug()<<nHexWithPre<<"\t"<<bok;   //字符 0x 打头自动按十六进制转

    int nDecAuto = strDec.toInt(&bok, 0);   //"800" ，自动按十进制
    qDebug()<<nDecAuto<<"\t"<<bok;

    //浮点数转换
    QString strFixed = QObject::tr("123.78999");
    double dblFixed = strFixed.toDouble(&bok);
    qDebug()<<fixed<<dblFixed<<"\t"<<bok;
    //科学计数法
    QString strScientific = QObject::tr("1.238e-5");
    double dblScientific = strScientific.toDouble(&bok);
    qDebug()<<scientific<<dblScientific<<"\t"<<bok;
}

void Test_operator()
{
    qDebug()<<"----------- Test_operator --------------------";
    // =
    QString strE1, strE2, strE3;
    strE1 = QObject::tr("abcd");
    strE2 = strE1;
    strE3 = strE2;
    //打印数据指针
    qDebug()<<strE1.data_ptr()<<"\t"<<strE2.data_ptr()<<"\t"<<strE3.data_ptr();
    //改变字符串，追加
    strE2.append( QObject::tr("1234") );
    //再次打印数据指针，谁修改了数据，谁的数据指针就变
    qDebug()<<strE1.data_ptr()<<"\t"<<strE2.data_ptr()<<"\t"<<strE3.data_ptr();

    // += 和 append 函数类似
    strE3 += QObject::tr("1234");
    qDebug()<<strE2<<"\t"<<strE3;

    //比较 1 vs 2
    qDebug()<<"strE1 < strE2: "<<(strE1 < strE2);
    qDebug()<<"strE1 <= strE2: "<<(strE1 <= strE2);
    qDebug()<<"strE1 == strE2: "<<(strE1 == strE2);
    qDebug()<<"strE1 != strE2: "<<(strE1 != strE2);
    //2 vs 3
    qDebug()<<"strE2 > strE3"<<(strE2 > strE3);
    qDebug()<<"strE2 >= strE3"<<(strE2 >= strE3);
    qDebug()<<"strE2 == strE3"<<(strE2 == strE3);

    //类似数组取数
    qDebug()<<strE1[0];
    strE1[0] = QChar('?');  //修改
    qDebug()<<strE1;

    //拼接
    QString strPlus;
    strPlus = strE1 + strE2 + strE3;
    qDebug()<<strPlus;
}

void Test_substring()
{
    qDebug()<<"----------- Test_substring --------------------";

    QString strOne = QObject::tr("abcd");
    QString strThree = strOne.repeated(3); //abcd 重复三次
    qDebug()<<strThree.isEmpty();   //是否为空
    qDebug()<<strThree.length()<<"\t"<<strThree.size(); //都是长度
    qDebug()<<strThree;

    //子串查询
    qDebug()<<strThree.contains(strOne);    //是否包含
    qDebug()<<strThree.count(strOne);       //包含几个
    qDebug()<<strThree.startsWith(strOne);  //打头的子串
    qDebug()<<strThree.indexOf(strOne);     //左边开始的子串位置
    qDebug()<<strThree.lastIndexOf(strOne); //右边开始的子串位置

    //剔除两端的空白
    QString strComplexFileName = QObject::tr("   /home/user/somefile.txt  \t\t ");
    QString strFileName = strComplexFileName.trimmed();
    qDebug()<<strFileName;
    if(strFileName.endsWith( QObject::tr(".txt") ))
    {
        qDebug()<<"This is a .txt file";
    }
    //分隔子串
    QStringList subsList = strFileName.split(QChar('/'));
    for(int i=0; i<subsList.length(); i++)  //打印各个子串
    {
        qDebug()<<i<<"\t"<<subsList[i];
    }
    //获取段落
    QString subsections = strFileName.section(QChar('/'), 2, 3);
    qDebug()<<subsections;
}

void Test_QTextStream()
{
    qDebug()<<"----------- Test_QTextStream --------------------";

    //内存输出流
    QString strOut;
    QTextStream streamOut(&strOut);
    //打印多种进制数字
    streamOut<<800<<endl;
    streamOut<<hex<<127<<endl;
    streamOut<<oct<<63<<endl;
    //还原为十进制
    streamOut<<dec;

    //设置域宽和填充字符
    streamOut<<qSetFieldWidth(8)<<qSetPadChar('0')<<800;
    //还原默认域宽和填充
    streamOut<<qSetFieldWidth(0)<<qSetPadChar(' ')<<endl;

    //设置精度
    streamOut<<qSetRealNumberPrecision(3)<<fixed<<123.789999<<endl;
    streamOut<<qSetRealNumberPrecision(6)<<scientific<<123.789999<<endl;

    //打印字符串和数字混搭
    streamOut<<QObject::tr("7*7 == ")<<7*7<<endl;
    //显示现在的字符串对象
    qDebug()<<strOut;


    //内存输入流
    QString strIn = QObject::tr("800  abcd  123.789999");
    QTextStream streamIn(&strIn);
    int numDec = 0;
    QString strSub;
    double dblReal = 0.0;
    //输入到变量里
    streamIn>>numDec>>strSub>>dblReal;
    //显示
    qDebug()<<numDec;
    qDebug()<<strSub;
    qDebug()<<fixed<<dblReal;   //定点数显示
}


void TestStr() //内码 UTF-8
{
    qDebug()<<"----------- TestStr --------------------";
    //数值与字符串转换
    int nDec = 800;
    QByteArray basDec;
    basDec.setNum(nDec);    //数值转字符串
    qDebug()<<basDec;
    QByteArray basReal = "125.78999";
    double dblReal = basReal.toDouble();    //字符串转数值
    qDebug()<<fixed<<dblReal;

    //运算符
    QByteArray basABCD = "ABCD";
    QByteArray basXYZ = "XYZ";
    qDebug()<<(basABCD < basXYZ);   //二者字符编码一致才能比较！
    qDebug()<<(basABCD == basXYZ);
    qDebug()<<(basABCD >= basXYZ);
    qDebug()<<(basABCD + basXYZ);

    //子串处理
    QByteArray basHanzi = "1234打印汉字";
    //作为字符串时 QByteArray::length() 和 qstrlen() 一致
    qDebug()<<basHanzi.length()<<"\t"<<qstrlen( basHanzi.data() );
    //重复
    QByteArray basMoreHanzi = basHanzi.repeated(2);
    qDebug()<<basMoreHanzi.count("1234"); //统计次数
    qDebug()<<basMoreHanzi.startsWith("1234");  //开头判断
    qDebug()<<basMoreHanzi.endsWith("汉字");     //结尾判断
    qDebug()<<basMoreHanzi.indexOf("1234");   //从左边查出现位置
    qDebug()<<basMoreHanzi.lastIndexOf("1234"); //从右边查出现位置
    //替换
    basMoreHanzi.replace("1234", "一二三四");
    qDebug()<<basMoreHanzi;

    //切割字符串
    QByteArray basComplexFile = "   /home/user/somefile.txt  \t\t ";
    QByteArray basFileName = basComplexFile.trimmed();  //剔除两端空白
    qDebug()<<basFileName;
    //分隔得到新的 QByteArray 对象列表
    QList<QByteArray> baList = basFileName.split('/');
    //打印
    for(int i=0; i<baList.length(); i++)
    {
        qDebug()<<i<<"\t"<<baList[i];
    }
    //没有段落函数
}

QByteArray TestSerialOut()
{
    qDebug()<<"----------- TestSerialOut --------------------";
    //数据
    int nVersion = 1;
    double dblValue = 125.78999;
    QString strName = QObject::tr("This an example.");
    //字节数组保存结果
    QByteArray baResult;
    //串行化的流
    QDataStream dsOut(&baResult, QIODevice::ReadWrite);  //做输出，构造函数用指针
    //设置Qt串行化版本
    dsOut.setVersion(QDataStream::Qt_5_0);//使用Qt 5.0 版本流
    //串行化输出
    dsOut<<nVersion<<dblValue<<strName;

    //显示长度
    qDebug()<<baResult.length()<<"\t"<<qstrlen(baResult.data());
    //返回对象
    return baResult;
}

void TestSerialIn(const QByteArray& baIn)
{
    qDebug()<<"----------- TestSerialIn --------------------";
    //输入流
    QDataStream dsIn(baIn); //只读的流，构造函数用常量引用
    //设置Qt串行化版本
    dsIn.setVersion(QDataStream::Qt_5_0);//使用Qt 5.0 版本流
    //变量
    int nVersion;
    double dblValue;
    QString strName;
    //串行化输入
    dsIn>>nVersion>>dblValue>>strName;

    //打印
    qDebug()<<nVersion;
    qDebug()<<fixed<<dblValue;
    qDebug()<<strName;
}

void TestCooperation()
{
    qDebug()<<"----------- TestCooperation --------------------";
    //源字符串
    QString strSrc = QObject::tr("1234abcd 千秋萬載 壹統江湖");
    //转为 UTF-8
    qDebug()<<strSrc.toUtf8();

    //明确地转为 GB18030
    QTextCodec *codecGB = QTextCodec::codecForName("GB18030");
    QByteArray strGB = codecGB->fromUnicode(strSrc); //转为GB18030
    qDebug()<<strGB;
    qDebug()<<codecGB->toUnicode(strGB);  //转回QString

    //明确地转为 Big5
    QTextCodec *codecBig5 = QTextCodec::codecForName("Big5");
    QByteArray strBig5 = codecBig5->fromUnicode(strSrc); //转为Big5
    qDebug()<<strBig5;
    qDebug()<<codecBig5->toUnicode(strBig5);    //转回QString
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Test_setNum();
    Test_arg();
    Test_toValue();
    Test_operator();
    Test_substring();
    Test_QTextStream();

    //测试QByteArray
    QString strText = QObject::tr("测试 QByteArray");
    QTextBrowser tb;
    tb.setText(strText);
    tb.setGeometry(40, 40, 400, 300);
    tb.show();

    //str
    TestStr();
    qDebug()<<endl;

    //serialization
    QByteArray baSerial = TestSerialOut();
    //baSerial 可用于网络发送
    //接收到 baSerial 之后解析
    TestSerialIn(baSerial);
    qDebug()<<endl;

    //测试协作
    TestCooperation();


    return a.exec();
}
