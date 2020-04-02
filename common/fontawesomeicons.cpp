#include "fontawesomeicons.h"
#include <QFontDatabase>
//这个类有两个作用：一是加载字体；二是将图标名称定义成枚举，方便后面使用。
FontAwesomeIcons &FontAwesomeIcons::Instance()
{
    static FontAwesomeIcons _instance;
    return _instance;
}

QFont FontAwesomeIcons::getFont()
{
    return this->font;
}

QChar FontAwesomeIcons::getIconChar(FontAwesomeIcons::IconIdentity code)
{
//    类型转换,然后返回,使用了新语法static_cast
    return QChar(static_cast<int>(code));
}

FontAwesomeIcons::FontAwesomeIcons()
{
    // add font file
    int fontId = QFontDatabase::addApplicationFont(":/res/font/fontawesome-webfont.ttf");
    QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);

    Q_ASSERT_X(fontFamilies.size()==1,"font","font not exist.");
//    设置字体样式
    this->font.setFamily(fontFamilies.at(0));
//    设置字体默认大小
    this->font.setPointSize(DEFAULT_FONT_SIZE);
}
