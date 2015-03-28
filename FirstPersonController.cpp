#include "FirstPersonController.h"

const float moveSpeed = 0.6;
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

   // Set the viewer's "eye" position, which is located at the center of the camera.
   osg::Vec3d eyePos;
   osg::Matrix matrix = _viewer->getCameraManipulator()->getMatrix();

   eyePos = matrix.getTrans();

   osg::Quat camRotation = matrix.getRotate();

   switch(ea.getEventType())
   {
      case(osgGA::GUIEventAdapter::KEYDOWN):
      {
         // Movement of the camera correlates with W, A, S, D
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

bool FirstPersonController::performMovement()
{
    // return if less then two events have been added
    if( _ga_t0.get() == NULL || _ga_t1.get() == NULL )
    {
        return false;
    }

    // get delta time, throw warning if error with delta time
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
    if( dx == 0.0 && dy == 0.0 )
    {
        return false;
    }


	//performMouseDeltaMovement(dx, dy);

    // call appropriate methods
    unsigned int buttonMask = _ga_t1->getButtonMask();
    if( buttonMask == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON )
    {
        return performMovementLeftMouseButton( eventTimeDelta, dx, dy );
    }
    else if( buttonMask == osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON ||
            buttonMask == (osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON | osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON) )
    {
        //return performMovementMiddleMouseButton( eventTimeDelta, dx, dy );
    }
    else if( buttonMask == osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON )
    {
        //return performMovementRightMouseButton( eventTimeDelta, dx, dy );
    }

    return false;
}


