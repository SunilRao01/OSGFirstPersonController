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


   }

   // Overload unnecessary functions from FirstPersonManipulator
   bool handleMouseWheel( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& us )
   {
       return true;
   };

   virtual bool performMovement();

   // Override handle function for keyboard input
   virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &);

   virtual void accept(osgGA::GUIEventHandlerVisitor &v)
    {
        v.visit(*this);
    };

protected:
   osgViewer::Viewer *_viewer;
   osg::Timer mainTimer;


};

#endif // FIRSTPERSONCONTROLLER_H
