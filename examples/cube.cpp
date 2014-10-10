#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>
#include <osgGA/TrackballManipulator>
#include <osgGA/FirstPersonManipulator>
#include <osg/MatrixTransform>
#include <osg/Matrixd>
#include <FirstPersonController.h>

// Variables
float tstep;

// Function
void update(osgViewer::Viewer &v);

// Main function
int main()
{
    //Create ROOT
    osg::ref_ptr<osg::Group> root (new osg::Group);

    //Create BOX
    osg::ref_ptr<osg::Box> myBox (new osg::Box(osg::Vec3(1, 1, 1), 1));
    osg::ref_ptr<osg::ShapeDrawable> boxDrawable (new osg::ShapeDrawable(myBox.get()));
    osg::ref_ptr<osg::Geode> myshapegeode (new osg::Geode);
    myshapegeode->addDrawable(boxDrawable.get());

    // Add cube
    root->addChild(myshapegeode);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());

    // KEYBOARD INPUT
    osg::ref_ptr<FirstPersonController> controller = new FirstPersonController(&viewer);


    // Connect viewer with keyboard handler
    viewer.addEventHandler(controller.get());

    //viewer.setUpViewInWindow(200, 200, 640, 480);
    viewer.realize();
    while (!viewer.done())
    {
        viewer.frame();
    }
}
