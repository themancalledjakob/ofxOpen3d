// ----------------------------------------------------------------------------
// -                        Open3D: www.open3d.org                            -
// ----------------------------------------------------------------------------
// The MIT License (MIT)
//
// Copyright (c) 2018-2021 www.open3d.org
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
// ----------------------------------------------------------------------------

#pragma once

// Note: do not modify Open3D.h, modify Open3D.h.in instead
#include "open3d/Open3DConfig.h"
#include "open3d/camera/PinholeCameraIntrinsic.h"
#include "open3d/camera/PinholeCameraParameters.h"
#include "open3d/camera/PinholeCameraTrajectory.h"
#include "open3d/core/Blob.h"
#include "open3d/core/DLPack.h"
#include "open3d/core/Device.h"
#include "open3d/core/Dtype.h"
#include "open3d/core/EigenConverter.h"
#include "open3d/core/FunctionTraits.h"
#include "open3d/core/MemoryManager.h"
#include "open3d/core/MemoryManagerStatistic.h"
#include "open3d/core/ShapeUtil.h"
#include "open3d/core/SizeVector.h"
#include "open3d/core/Tensor.h"
#include "open3d/core/TensorCheck.h"
#include "open3d/core/TensorKey.h"
#include "open3d/core/TensorList.h"
#include "open3d/core/nns/NearestNeighborSearch.h"
#include "open3d/data/Dataset.h"
#include "open3d/geometry/BoundingVolume.h"
#include "open3d/geometry/Geometry.h"
#include "open3d/geometry/HalfEdgeTriangleMesh.h"
#include "open3d/geometry/Image.h"
#include "open3d/geometry/KDTreeFlann.h"
#include "open3d/geometry/Keypoint.h"
#include "open3d/geometry/Line3D.h"
#include "open3d/geometry/LineSet.h"
#include "open3d/geometry/Octree.h"
#include "open3d/geometry/PointCloud.h"
#include "open3d/geometry/RGBDImage.h"
#include "open3d/geometry/TriangleMesh.h"
#include "open3d/geometry/VoxelGrid.h"
#include "open3d/io/FeatureIO.h"
#include "open3d/io/FileFormatIO.h"
#include "open3d/io/IJsonConvertibleIO.h"
#include "open3d/io/ImageIO.h"
#include "open3d/io/LineSetIO.h"
#include "open3d/io/ModelIO.h"
#include "open3d/io/PinholeCameraTrajectoryIO.h"
#include "open3d/io/PointCloudIO.h"
#include "open3d/io/PoseGraphIO.h"
#include "open3d/io/TriangleMeshIO.h"
#include "open3d/io/VoxelGridIO.h"
#include "open3d/pipelines/color_map/NonRigidOptimizer.h"
#include "open3d/pipelines/color_map/RigidOptimizer.h"
#include "open3d/pipelines/integration/ScalableTSDFVolume.h"
#include "open3d/pipelines/integration/TSDFVolume.h"
#include "open3d/pipelines/integration/UniformTSDFVolume.h"
#include "open3d/pipelines/odometry/Odometry.h"
#include "open3d/pipelines/registration/ColoredICP.h"
#include "open3d/pipelines/registration/FastGlobalRegistration.h"
#include "open3d/pipelines/registration/Feature.h"
#include "open3d/pipelines/registration/GeneralizedICP.h"
#include "open3d/pipelines/registration/Registration.h"
#include "open3d/pipelines/registration/TransformationEstimation.h"
#include "open3d/t/geometry/Geometry.h"
#include "open3d/t/geometry/Image.h"
#include "open3d/t/geometry/PointCloud.h"
#include "open3d/t/geometry/RGBDImage.h"
#include "open3d/t/geometry/TensorMap.h"
#include "open3d/t/geometry/TriangleMesh.h"
#include "open3d/t/geometry/VoxelBlockGrid.h"
#include "open3d/t/io/HashMapIO.h"
#include "open3d/t/io/ImageIO.h"
#include "open3d/t/io/NumpyIO.h"
#include "open3d/t/io/PointCloudIO.h"
#include "open3d/t/pipelines/kernel/TransformationConverter.h"
#include "open3d/t/pipelines/odometry/RGBDOdometry.h"
#include "open3d/t/pipelines/registration/Registration.h"
#include "open3d/t/pipelines/registration/TransformationEstimation.h"
#include "open3d/t/pipelines/slac/ControlGrid.h"
#include "open3d/t/pipelines/slac/SLACOptimizer.h"
#include "open3d/t/pipelines/slam/Frame.h"
#include "open3d/t/pipelines/slam/Model.h"
#include "open3d/utility/CPUInfo.h"
#include "open3d/utility/CompilerInfo.h"
#include "open3d/utility/Console.h"
#include "open3d/utility/Eigen.h"
#include "open3d/utility/FileSystem.h"
#include "open3d/utility/Helper.h"
#include "open3d/utility/ISAInfo.h"
#include "open3d/utility/Logging.h"
#include "open3d/utility/Parallel.h"
#include "open3d/utility/ProgressBar.h"
#include "open3d/utility/ProgressReporters.h"
#include "open3d/utility/Timer.h"
// #include "open3d/visualization/gui/Application.h"
// #include "open3d/visualization/gui/Button.h"
// #include "open3d/visualization/gui/Checkbox.h"
// #include "open3d/visualization/gui/Color.h"
// #include "open3d/visualization/gui/Combobox.h"
// #include "open3d/visualization/gui/Dialog.h"
// #include "open3d/visualization/gui/Gui.h"
// #include "open3d/visualization/gui/ImageWidget.h"
// #include "open3d/visualization/gui/Label.h"
// #include "open3d/visualization/gui/Layout.h"
// #include "open3d/visualization/gui/Menu.h"
// #include "open3d/visualization/gui/ProgressBar.h"
// #include "open3d/visualization/gui/SceneWidget.h"
// #include "open3d/visualization/gui/Slider.h"
// #include "open3d/visualization/gui/TabControl.h"
// #include "open3d/visualization/gui/TextEdit.h"
// #include "open3d/visualization/gui/Theme.h"
// #include "open3d/visualization/gui/ToggleSwitch.h"
// #include "open3d/visualization/gui/TreeView.h"
// #include "open3d/visualization/gui/Window.h"
// #include "open3d/visualization/rendering/Material.h"
// #include "open3d/visualization/rendering/Model.h"
// #include "open3d/visualization/rendering/Open3DScene.h"
// #include "open3d/visualization/utility/Draw.h"
// #include "open3d/visualization/utility/DrawGeometry.h"
// #include "open3d/visualization/utility/SelectionPolygon.h"
// #include "open3d/visualization/utility/SelectionPolygonVolume.h"
// #include "open3d/visualization/visualizer/O3DVisualizer.h"
// #include "open3d/visualization/visualizer/ViewControl.h"
// #include "open3d/visualization/visualizer/ViewControlWithCustomAnimation.h"
// #include "open3d/visualization/visualizer/ViewControlWithEditing.h"
// #include "open3d/visualization/visualizer/Visualizer.h"
// #include "open3d/visualization/visualizer/VisualizerWithCustomAnimation.h"
// #include "open3d/visualization/visualizer/VisualizerWithEditing.h"
// #include "open3d/visualization/visualizer/VisualizerWithKeyCallback.h"
// #include "open3d/visualization/visualizer/VisualizerWithVertexSelection.h"

// clang-format off
//#include "open3d/io/sensor/azure_kinect/AzureKinectRecorder.h"
//#include "open3d/io/sensor/azure_kinect/AzureKinectSensorConfig.h"
//#include "open3d/io/sensor/azure_kinect/AzureKinectSensor.h"
//#include "open3d/io/sensor/azure_kinect/MKVMetadata.h"
//#include "open3d/io/sensor/azure_kinect/MKVReader.h"
//#include "open3d/io/sensor/azure_kinect/MKVWriter.h"
//#include "open3d/io/sensor/RGBDRecorder.h"
//#include "open3d/io/sensor/RGBDSensorConfig.h"
//#include "open3d/io/sensor/RGBDSensor.h"

// #include "open3d/t/io/sensor/realsense/RSBagReader.h"
// #include "open3d/t/io/sensor/realsense/RealSenseSensor.h"

// #include "open3d/visualization/webrtc_server/WebRTCWindowSystem.h"
