#ifndef FIRSTPERSONCONTROLLER_H
#define FIRSTPERSONCONTROLLER_H

#include <osg/MatrixTransform>
#include <osgGA/FirstPersonManipulator>
#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>
#include <osg/Timer>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

class FirstPersonController : public osgGA::FirstPersonManipulator
{
public:
   FirstPersonController(osgViewer::Viewer *inputViewer) : _viewer(inputViewer)
   {
        mainTimer.setStartTick();
        //_viewer->setCameraManipulator(new FirstPersonPerspective);
        //_viewer->setCameraManipulator(new osgGA::FirstPersonManipulator);
   }

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
