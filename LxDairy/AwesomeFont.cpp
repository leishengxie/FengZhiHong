#include "AwesomeFont.h"

#include <QFontDatabase>

bool CAwesomeFont::s_bInitFont = false;
QFont CAwesomeFont::s_iconFont;

CAwesomeFont::CAwesomeFont(QObject *parent)
    : QObject(parent)
{
    initFont();
}

void CAwesomeFont::setIcon(QLabel *label, QChar ch, int nPoitSize)
{
    s_iconFont.setPointSize(nPoitSize);
    lab->setFont(s_iconFont);
    lab->setText(ch);
}

void CAwesomeFont::setIcon(QPushButton *btn, QChar ch, int nPoitSize)
{
    s_iconFont.setPointSize(nPoitSize);
    btn->setFont(s_iconFont);
    btn->setText(ch);
}

void CAwesomeFont::initFont()
{
    if (s_bInitFont)
    {
        return;
    }
    int fontId = QFontDatabase::addApplicationFont(":/font/fontawesome-webfont.ttf");
    QString fontName = QFontDatabase::applicationFontFamilies(fontId).at(0);
    s_iconFont = QFont(fontName);
    s_bInitFont = true;
}
