/*
    This file is part of the Fido Plugin for Retroshare.

    Fido is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Fido is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Fido.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "FidoPlugin.h"
#include "p3Fido.h"


#include <retroshare/rsplugin.h>
#include <retroshare/rsversion.h>

#include <QApplication>
#include <QTranslator>
#include <QMessageBox>



FidoPlugin * FidoPlugin::fidoPlugin;

extern "C" {
    void * RETROSHARE_PLUGIN_provide()
	{
        FidoPlugin::fidoPlugin = new FidoPlugin() ;
        return (void*) FidoPlugin::fidoPlugin;
	}
	// This symbol contains the svn revision number grabbed from the executable. 
	// It will be tested by RS to load the plugin automatically, since it is safe to load plugins
	// with same revision numbers, assuming that the revision numbers are up-to-date.
	//
	uint32_t RETROSHARE_PLUGIN_revision = RS_REVISION_NUMBER ;

	// This symbol contains the svn revision number grabbed from the executable. 
	// It will be tested by RS to load the plugin automatically, since it is safe to load plugins
	// with same revision numbers, assuming that the revision numbers are up-to-date.
	//
	uint32_t RETROSHARE_PLUGIN_api = RS_PLUGIN_API_VERSION ;
}

#define IMAGE_LINKS ":/images/tortoise.png"

void FidoPlugin::getPluginVersion(int& major,int& minor,int& build,int& svn_rev) const
{
    major = RS_MAJOR_VERSION;
    minor = RS_MINOR_VERSION;
    build = RS_BUILD_NUMBER;
    svn_rev = RS_REVISION_NUMBER ;
}


FidoPlugin::FidoPlugin() :
    m_Fido( NULL )
{
}

void FidoPlugin::setInterfaces(RsPlugInInterfaces &interfaces)
{
}


void FidoPlugin::setPlugInHandler(RsPluginHandler *pgHandler)
{
    m_PlugInHandler = pgHandler;
    m_Fido = new p3Fido(m_PlugInHandler);
}



RsPQIService * FidoPlugin::rs_pqi_service() const
{
    if(m_Fido == NULL){
        m_Fido = new p3Fido(m_PlugInHandler ) ;
    }
    return m_Fido;
}

std::string FidoPlugin::getShortPluginDescription() const
{
    return QApplication::translate("FidoPlugin", "This plugin implements an SMTP mail <-> RS Messaging gateway").toUtf8().constData();
}

std::string FidoPlugin::getPluginName() const
{
    return QApplication::translate("FidoPlugin", "Fido" ).toUtf8().constData();
}

QDialog * FidoPlugin::qt_about_page() const
{
    static QMessageBox *about_dialog = NULL;
    m_Fido->tick();

    if(about_dialog == NULL)
    {
        about_dialog = new QMessageBox() ;

        QString text ;
        text += QObject::tr("<h3>RetroShare Fido plugin</h3><br/>Email to RetroShare Messaging Gateway<br/>" ) ;

        about_dialog->setText(text) ;
        about_dialog->setStandardButtons(QMessageBox::Ok) ;
    }

    return about_dialog ;
}



