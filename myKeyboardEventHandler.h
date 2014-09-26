#ifndef MYKEYBOARDEVENTHANDLER_H
#define MYKEYBOARDEVENTHANDLER_H

#include <osg/MatrixTransform>
#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>
#include <iostream>

class myKeyboardEventHandler : public osgGA::GUIEventHandler
{
public:
   myKeyboardEventHandler(osg::MatrixTransform *node) : _model(node)
   {

   }

   virtual bool handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &);

   virtual void accept(osgGA::GUIEventHandlerVisitor &v)
    {
        v.visit(*this);
    };
protected:
   osg::ref_ptr<osg::MatrixTransform> _model;
};

#endif // MYKEYBOARDEVENTHANDLER_H
