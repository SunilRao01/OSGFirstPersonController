#ifndef FIRSTPERSONCONTROLLER_H
#define FIRSTPERSONCONTROLLER_H

#include <osg/MatrixTransform>
#include <osgGA/FirstPersonManipulator>
#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>
#include <osg/Timer>
#include <osgText/Text>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

class FirstPersonController : public osgGA::FirstPersonManipulator
{
public:
   FirstPersonController(osgViewer::Viewer *inputViewer) : _viewer(inputViewer)
   {
       // Start frame timer
       mainTimer.setStartTick();


       // Add HUD
       _viewer->setUpViewAcrossAllScreens();
       osgViewer::Viewer::Windows windows;
       _viewer->getWindows(windows);

       if (windows.empty())
       {
           std::cout << "No windows for viewer found...";
       }

       osg::Camera *hudCam = createHUD();

       hudCam->setGraphicsContext(windows[0]);
       hudCam->setViewport(0, 0, windows[0]->getTraits()->width, windows[0]->getTraits()->height);

       _viewer->addSlave(hudCam, false);
   }

   // Overload unnecessary functions from FirstPersonManipulator
   bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
   {
       return true;
   };

   // Override StandardManipulator's performMovment function to get rid of requirement
   // to hold left mouse button to look around
   virtual bool performMovement();

   // Override handle function for keyboard input
   virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &);

   virtual void accept(osgGA::GUIEventHandlerVisitor &v)
    {
        v.visit(*this);
    };

   osg::Camera *createHUD();
protected:
   osgViewer::Viewer *_viewer;
   osg::Timer mainTimer;


};

#endif // FIRSTPERSONCONTROLLER_H
