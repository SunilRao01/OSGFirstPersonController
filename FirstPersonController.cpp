#include "FirstPersonController.h"

const float moveSpeed = 0.1;
const float inputTimeInterval = 0.02;

osg::Vec3d tempMov;
double maxTick = inputTimeInterval;

bool FirstPersonController::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{

    // Still use first person manipulator for camera movements (Inherited class function)
    FirstPersonManipulator::handle(ea, aa);

   if (!_viewer)
   {
       return false;
   }

   osg::Vec3d eyePos;
   osg::Matrix matrix = _viewer->getCameraManipulator()->getMatrix();

   eyePos = matrix.getTrans();

   osg::Quat camRotation = matrix.getRotate();

   switch(ea.getEventType())
   {
      case(osgGA::GUIEventAdapter::KEYDOWN):
      {
         // Relies on keyboard input
         switch(ea.getKey())
         {
             case 'w':
                tempMov.z() = -moveSpeed;

                break;
             case 'a':
                 tempMov.x() = -moveSpeed;

                 break;
             case 's':
                 tempMov.z() = moveSpeed;

                 break;
             case 'd':
                 tempMov.x() = moveSpeed;

                 break;
             default:
                 break;
         }

        default:
         break;
      }

       case(osgGA::GUIEventAdapter::KEYUP):
       {
            switch(ea.getKey())
            {
               case 'w':
                   tempMov.set(0, 0, 0);
                   break;
               case 'a':
                   tempMov.set(0, 0, 0);
                   break;
               case 's':
                   tempMov.set(0, 0, 0);
                   break;
               case 'd':
                   tempMov.set(0, 0, 0);
                   break;
               default:
                   break;
            }

            //default:
            break;
       }

    }
   eyePos += camRotation * tempMov;
   matrix.setTrans(eyePos);

    // Check [mainTimer.time % (time divisor) == 0]
   if (mainTimer.time_s() >= maxTick)
   {
       _viewer->getCameraManipulator()->setByMatrix(matrix);
       maxTick += inputTimeInterval;
   }

    return false;
}

osg::Camera *FirstPersonController::createHUD()
{
    // Create new camera for HUD
    osg::Camera *cam = new osg::Camera();

    // Set the camera's projection matrix
    cam->setProjectionMatrix(osg::Matrix::ortho2D(0, 1280, 0, 1024));

    // Set the view matrix
    cam->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    cam->setViewMatrix(osg::Matrix::identity());

    // Clear the camera's depth buffer
    cam->setClearMask(GL_DEPTH_BUFFER_BIT);

    // Draw subgraph after main camera view
    cam->setRenderOrder(osg::Camera::POST_RENDER);

    // Don't override main camera's event focus
    cam->setAllowEventFocus(false);


    // What the HUD camera will render
    osg::Geode *geode = new osg::Geode();

    std::string hudFont("fonts/Bretan.otf");

    osg::StateSet* stateset = geode->getOrCreateStateSet();
    stateset->setMode(GL_LIGHTING,osg::StateAttribute::OFF);

    osg::Vec3 position(150.0f,800.0f,0.0f);
    osg::Vec3 delta(0.0f,-120.0f,0.0f);

    {
        osgText::Text *text = new  osgText::Text();
        geode->addDrawable(text);

        text->setFont(hudFont);
        text->setPosition(position);

        text->setText("Virtual UIC");

        position += delta;
    }

    {
        osg::BoundingBox bb;
        for (int i = 0; i < geode->getNumDrawables(); ++i)
        {
            bb.expandBy(geode->getDrawable(i)->getBound());
        }

        osg::Geometry *geom = new osg::Geometry();

        osg::Vec3Array *vertices = new osg::Vec3Array();
        float depth = bb.zMin() - 0.1;

        vertices->push_back(osg::Vec3(bb.xMin(), bb.yMin(), depth));
        vertices->push_back(osg::Vec3(bb.xMin(), bb.yMin(), depth));
        vertices->push_back(osg::Vec3(bb.xMin(), bb.yMin(), depth));
        vertices->push_back(osg::Vec3(bb.xMin(), bb.yMin(), depth));
        geom->setVertexArray(vertices);

        osg::Vec3Array *normals = new osg::Vec3Array();
        normals->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
        geom->setNormalArray(normals, osg::Array::BIND_OVERALL);

        osg::Vec4Array *colors = new osg::Vec4Array();
        colors->push_back(osg::Vec4(1.0f, 1.0f, 0.8f, 0.2f));
        geom->setColorArray(colors, osg::Array::BIND_OVERALL);

        geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));

        osg::StateSet *stateSet = geom->getOrCreateStateSet();
        stateSet->setMode(GL_BLEND, osg::StateAttribute::ON);
        stateSet->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

        geode->addDrawable(geom);

        cam->addChild(geode);
    }

    return cam;
}

bool FirstPersonController::performMovement()
{
    //StandardManipulator::performMovement();
    //FirstPersonManipulator::performMovement();

    // return if less then two events have been added
    if( _ga_t0.get() == NULL || _ga_t1.get() == NULL )
        return false;

    // get delta time
    double eventTimeDelta = _ga_t0->getTime() - _ga_t1->getTime();
    if( eventTimeDelta < 0. )
    {
        OSG_WARN << "Manipulator warning: eventTimeDelta = " << eventTimeDelta << std::endl;
        eventTimeDelta = 0.;
    }

    // get deltaX and deltaY
    float dx = _ga_t0->getXnormalized() - _ga_t1->getXnormalized();
    float dy = _ga_t0->getYnormalized() - _ga_t1->getYnormalized();

    // return if there is no movement.
    if( dx == 0. && dy == 0. )
        return false;

    return performMovementLeftMouseButton( eventTimeDelta, dx, dy );
    // call appropriate methods
    unsigned int buttonMask = _ga_t1->getButtonMask();
    if( buttonMask == osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON )
    {
        return performMovementLeftMouseButton( eventTimeDelta, dx, dy );
    }
    else if( buttonMask == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON ||
            buttonMask == (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON | osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) )
    {
        return performMovementMiddleMouseButton( eventTimeDelta, dx, dy );
    }
    else if( buttonMask == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON )
    {
        return performMovementRightMouseButton( eventTimeDelta, dx, dy );
    }

    return false;


}


