OSGFirstPersonController
========================

A first person controller using the OpenSceneGraph C++ library.

In order to use this, simply include the header in your main and instantiate FirstPersonContrller
while giving a reference to your osgViewer object as a parameter. Then add the controller to your
viewer as an event handler.

NOTE: You currently have to hold the mouse down to utilize the first person camera. This is a bug
that is planned on being fixed shortly.
