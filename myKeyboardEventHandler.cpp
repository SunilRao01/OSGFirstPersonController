#include "myKeyboardEventHandler.h"


bool myKeyboardEventHandler::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
   if (!_model)
   {
       return false;
   }

   osg::Matrix matrix = _model->getMatrix();

   switch(ea.getEventType())
   {
        case(osgGA::GUIEventAdapter::KEYDOWN):
          {
             switch(ea.getKey())
             {
             case 'w':
                //std::cout << "w key pressed" << std::endl;
                matrix *= osg::Matrix::rotate(-0.1f, osg::X_AXIS);
                //return false;
                break;
             case 'a':
                //std::cout << "a key pressed" << std::endl;
                 matrix *= osg::Matrix::rotate(-0.1f, osg::X_AXIS);
                //return false;
                break;
             case 's':
                //std::cout << "s key pressed" << std::endl;
                 matrix *= osg::Matrix::rotate(0.1f, osg::X_AXIS);
                //return false;
                break;
             case 'd':
               // std::cout << "d key pressed" << std::endl;
                  matrix *= osg::Matrix::rotate(0.1f, osg::Z_AXIS);
               // return false;
                break;
             default:
                 break;
             }

             _model->setMatrix(matrix);
             break;

            default:
                 break;
          }

        return false;
   }
}

