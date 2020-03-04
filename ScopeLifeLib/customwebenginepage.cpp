#include "customwebenginepage.h"

CustomWebEnginePage::CustomWebEnginePage()
{
    connect(this,&QWebEnginePage::featurePermissionRequested, this,&CustomWebEnginePage::featureControl);

}




void CustomWebEnginePage::startWebCapture(QUrl url)
{
    emit startCapture(url);
}

void CustomWebEnginePage::featureControl(const QUrl &origin, QWebEnginePage::Feature feature)
{
//    this->featureControl(origin, QWebEnginePage::DesktopAudioVideoCapture);
    qDebug()<<"feature "<< feature;
   this->setFeaturePermission(origin,feature,QWebEnginePage::PermissionGrantedByUser);

}

bool CustomWebEnginePage::certificateError(const QWebEngineCertificateError &certificateError)
{
    return true;
}

bool CustomWebEnginePage::acceptNavigationRequest(const QUrl &url, QWebEnginePage::NavigationType type, bool isMainFrame)
{
qDebug()<<"acceptNavigationRequest in CustomWebEnginePage "<< type<<url;



       if(url.toString().indexOf("snap")!=-1){
//                       this->runJavaScript("alert('ok')");
         qDebug()<<"SNAP "<<this;
//                        this->startWebCapture(url);
         emit startCapture(url);


       return true;

        }else{

    switch( type )
      {
          case QWebEnginePage::NavigationTypeLinkClicked:
          {
            qDebug()<<"NAV "<<url;

//              mLastClickedLink = url; //-- clear it in CustomWebEnginePage::createWindow

            //    http://colo.emr-life.com/esm_image/113/snap?field_id=F8377840798&p_id=91&path=esm/colo/colo/test/colonoscopy/2017-05-24-592474b8790f9b3963000002/image&ref=test&ref_2=tste seff
            //    http://colo.emr-life.com/esm_image/145/snap?field_id=F8377840798&p_id=91&path=esm/colo/colo/test/gastroscopy/2017-05-24-592475fc790f9b3963000005/image&ref=test&ref_2=tste seff
            //    hn = ref
            //      name = ref_2
            //      id = 592474b8790f9b3963000002
            //      form = colonoscopy
            //      field id = F8377840798
//                if(url.toString().indexOf("snap")!=-1){
////                       this->runJavaScript("alert('ok')");
//                         qDebug()<<"SNAP "<<this;
////                        this->startWebCapture(url);
//                         emit startCapture(url);


//                    return false;

//                }else{

//                     return true;
//                }
////
            return  QWebEnginePage::acceptNavigationRequest( url, type, isMainFrame );

          }

       default:
              return QWebEnginePage::acceptNavigationRequest( url, type, isMainFrame );
      }
       }


    return true;
}


QWebEnginePage *CustomWebEnginePage::createWindow(QWebEnginePage::WebWindowType type)
{
     qDebug()<<"create Window "<< type;
     switch (type) {
        case QWebEnginePage::WebBrowserTab: {

         qDebug()<<"xxxxcreate tab ";


//            emit startCapture(this->url());


            CustomWebEnginePage *page = new CustomWebEnginePage();
            QObject::connect(page, SIGNAL(startCapture(QUrl)),this, SLOT(startWebCapture(QUrl)));


//         qDebug()<<

//            BrowserWindow *mainWindow = qobject_cast<BrowserWindow*>(window());
//            return mainWindow->tabWidget()->createTab();
         return page;

        }

        case QWebEnginePage::WebBrowserWindow: {
         qDebug()<<"xxxxcreate Window ";

//            BrowserWindow *mainWindow = new BrowserWindow();
//            Browser::instance().addWindow(mainWindow);
//            return mainWindow->currentTab();
         return this;

        }
        case QWebEnginePage::WebDialog: {
         qDebug()<<"xxxxopen Dialogxxxxx ";

//            WebPopupWindow *popup = new WebPopupWindow(page()->profile());
//            return popup->view();
         return this;

        }
        }
        return this;


}

bool CustomWebEnginePage::javaScriptConfirm(const QUrl &securityOrigin, const QString &msg)
{


        qDebug()<<"Confirm";
        return true;
}

void CustomWebEnginePage::javaScriptAlert(const QUrl &securityOrigin, const QString &msg)
{
    qDebug()<<"Alert";
}

void CustomWebEnginePage::javaScriptConsoleMessage(QWebEnginePage::JavaScriptConsoleMessageLevel level, const QString &message, int lineNumber, const QString &sourceID)
{
//        qDebug()<<"Console " <<message;
    emit consoleMessage(level, message);
}
