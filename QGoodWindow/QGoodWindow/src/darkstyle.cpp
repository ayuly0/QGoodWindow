/*
The MIT License (MIT)

Copyright © 2018, Juergen Skrotzky (https://github.com/Jorgen-VikingGod, JorgenVikingGod@gmail.com)
Copyright © 2018-2024 Antonio Dias (https://github.com/antonypro)

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "darkstyle.h"
#include "stylecommon.h"

DarkStyle::DarkStyle() : DarkStyle( styleBase() )
{
#ifdef Q_OS_WIN
    m_hash_pixmap_cache[ SP_MessageBoxInformation ] = StyleCommon::winStandardPixmap( SP_MessageBoxInformation );
    m_hash_pixmap_cache[ SP_MessageBoxWarning ]     = StyleCommon::winStandardPixmap( SP_MessageBoxWarning );
    m_hash_pixmap_cache[ SP_MessageBoxCritical ]    = StyleCommon::winStandardPixmap( SP_MessageBoxCritical );
    m_hash_pixmap_cache[ SP_MessageBoxQuestion ]    = StyleCommon::winStandardPixmap( SP_MessageBoxQuestion );
#endif
}

DarkStyle::DarkStyle( QStyle *style ) : QProxyStyle( style )
{
}

DarkStyle::~DarkStyle()
{
}

QStyle *DarkStyle::styleBase() const
{
    QStyle *base = QStyleFactory::create( QStringLiteral( "Fusion" ) );
    return base;
}

QIcon DarkStyle::standardIcon( StandardPixmap standardPixmap, const QStyleOption *option, const QWidget *widget ) const
{
#ifdef Q_OS_WIN
    switch ( standardPixmap )
    {
    case SP_MessageBoxInformation:
    case SP_MessageBoxWarning:
    case SP_MessageBoxCritical:
    case SP_MessageBoxQuestion   : {
        QPixmap pixmap = m_hash_pixmap_cache.value( standardPixmap, QPixmap() );

        if ( !pixmap.isNull() )
        {
            return QIcon( pixmap );
        }

        break;
    }
    default: break;
    }
#endif

    return QProxyStyle::standardIcon( standardPixmap, option, widget );
}

void DarkStyle::polish( QPalette &palette )
{
    QColor windowColor( "#292b2f" );
    QColor windowTextColor( "#FFFFFF" );
    QColor disabledTextColor( "#7F7F7F" );
    QColor baseColor( "#202225" );
    QColor alternateBaseColor( "#2F3136" );
    QColor tooltipBaseColor( "#FFFFFF" );
    QColor tooltipTextColor( "#FFFFFF" );
    QColor textColor( "#FFFFFF" );
    QColor darkColor( "#202225" );
    QColor shadowColor( "#141414" );
    QColor buttonColor( "#202225" );
    QColor buttonTextColor( "#FFFFFF" );
    QColor brightTextColor( "#FF0000" );
    QColor linkColor( "#2A82DA" );
    QColor highlightColor( "#2A82DA" );
    QColor disabledHighlightColor( "#505050" );
    QColor highlightedTextColor( "#FFFFFF" );

    palette.setColor( QPalette::Window, windowColor );
    palette.setColor( QPalette::WindowText, windowTextColor );
    palette.setColor( QPalette::Disabled, QPalette::WindowText, disabledTextColor );
    palette.setColor( QPalette::Base, baseColor );
    palette.setColor( QPalette::AlternateBase, alternateBaseColor );
    palette.setColor( QPalette::ToolTipBase, tooltipBaseColor );
    palette.setColor( QPalette::ToolTipText, tooltipTextColor );
    palette.setColor( QPalette::Text, textColor );
    palette.setColor( QPalette::Disabled, QPalette::Text, disabledTextColor );
    palette.setColor( QPalette::Dark, darkColor );
    palette.setColor( QPalette::Shadow, shadowColor );
    palette.setColor( QPalette::Button, buttonColor );
    palette.setColor( QPalette::ButtonText, buttonTextColor );
    palette.setColor( QPalette::Disabled, QPalette::ButtonText, disabledTextColor );
    palette.setColor( QPalette::BrightText, brightTextColor );
    palette.setColor( QPalette::Link, linkColor );
    palette.setColor( QPalette::Highlight, highlightColor );
    palette.setColor( QPalette::Disabled, QPalette::Highlight, disabledHighlightColor );
    palette.setColor( QPalette::HighlightedText, highlightedTextColor );
    palette.setColor( QPalette::Disabled, QPalette::HighlightedText, disabledTextColor );
}

void DarkStyle::polish( QApplication *app )
{
    if ( !app )
    {
        return;
    }

    QFont defaultFont = app->font();
    defaultFont.setPointSize( defaultFont.pointSize() + 2 );
    app->setFont( defaultFont );

    QFile file( QStringLiteral( ":/darkstyle.qss" ) );

    if ( file.open( QFile::ReadOnly | QFile::Text ) )
    {
        QString style_sheet = QLatin1String( file.readAll() );
        app->setStyleSheet( style_sheet );
        file.close();
    }
}

void DarkStyle::unpolish( QApplication *app )
{
    if ( !app )
    {
        return;
    }

    QFont defaultFont = app->font();
    defaultFont.setPointSize( defaultFont.pointSize() - 2 );
    app->setFont( defaultFont );
}

QStyle *DarkStyle::baseStyle() const
{
    return styleBase();
}
