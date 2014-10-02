#include "myKeyboardEventHandler.h"

const float moveSpeed = 0.02;
const float timeInterval = 0.02;

osg::Vec3d tempMov;
double maxTick = timeInterval;

bool myKeyboardEventHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{

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

   // TODO: Print out timer for smoothing


    // Check [mainTimer.time % (time divisor) == 0]
   if (mainTimer.time_s() >= maxTick)
   {
       _viewer->getCameraManipulator()->setByMatrix(matrix);
       maxTick += timeInterval;
   }


}

