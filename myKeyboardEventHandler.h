#ifndef MYKEYBOARDEVENTHANDLER_H
#define MYKEYBOARDEVENTHANDLER_H

#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>
#include <osg/Timer>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>

class myKeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
   myKeyboardEventHandler(osgViewer::Viewer *inputViewer) : _viewer(inputViewer)
   {
        mainTimer.setStartTick();
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

#endif // MYKEYBOARDEVENTHANDLER_H
