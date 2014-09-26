#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osg/MatrixTransform>
#include <myKeyboardEventHandler.h>

// Main function
int main()
{
    //Creating the root node
    osg::ref_ptr<osg::Group> root (new osg::Group);

    // CYLINDER NODE
    //The geode containing our shape
    osg::ref_ptr<osg::Geode> myshapegeode (new osg::Geode);

    //Create a box
    osg::ref_ptr<osg::Box> myBox (new osg::Box(osg::Vec3(1, 1, 1), 1));

    //Add box shape to OSG drawable
    osg::ref_ptr<osg::ShapeDrawable> boxDrawable (new osg::ShapeDrawable(myBox.get()));

    // Add drawable (containing the box) to geode
    myshapegeode->addDrawable(boxDrawable.get());

    // Matrix Transform of cube
    osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
    mt->addChild(myshapegeode.get());
    // Add geode node to OSG graph
    root->addChild(mt.get());

    // KEYBOARD INPUT
    // Create keyboard event handler
    osg::ref_ptr<myKeyboardEventHandler> controller = new myKeyboardEventHandler(mt.get());


    //Creating the viewer
    osgViewer::Viewer viewer;

    // Add keyboard event handler to osgviewer
    viewer.addEventHandler(controller.get());

    viewer.getCamera()->setViewMatrixAsLookAt(osg::Vec3(10.0f, -10.0f, 10.0f), osg::Vec3(), osg::Z_AXIS);
    viewer.getCamera()->setAllowEventFocus(false);



    // Connect OSG viewer with the OSG graph's root node
    viewer.setSceneData(root.get());

    /*if (!viewer.done())
    {
        viewer.frame();

        customUpdate(*customTransformation);
    }*/


    //The viewer.run() method starts the threads and the traversals.
    return (viewer.run());
}
