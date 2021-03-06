/*
 Copyright 2010 Benjamin Loulier <http://www.benjaminloulier.com> <benlodotcom@gmail.com>
 
 This program is free software: you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program.  If not, see <http://www.gnu.org/licenses/>
*/

#import <Foundation/Foundation.h>
#import <CoreVideo/CoreVideo.h>

@class ARToolKitPlusWrapper;

/*!
	@author Benjamin Loulier

	@brief	This protocol describes the delegates methods that the delegate of an ARToolKitPlusWrapper instance must implement

	An ARToolKitPlusWrapper instance use the delegate pattern to send back datas when it is initialized and when
	a marker is or is not detected. This protocol describes the methods that the ARToolKitPlusWrapper instance calls
	on its delegate.\n
	For now only single marker detection is implemented.
*/
@protocol ARToolKitPlusWrapperDelegate

/*!
	@brief	When the wrapper can auto setup with a frame sample, the only constraint for now is that the images has to be in BGRA.

	@param	wrapper The ARToolKitPlusWrapper instance calling its delegate
	@param	projectionMatrix The OpenGL projection matrix generated by ARToolKitPLus
*/
- (void)aRToolKitPlusWrapper:(ARToolKitPlusWrapper *)wrapper didSetupWithProjectionMatrix:(NSArray *)projectionMatrix;
/*!
	@brief	When the wrapper has processed a frame to detect a marker this method is called on its delegate.

	This method send informations neeed to display an object in virtual reality.
	@param	wrapper The ARToolKitPlusWrapper instance calling its delegate
	@param	markerID The ID of the marker detected (-1 if no marker detected)
	@param	confidence 
	@param	modelViewMatrix The OpenGL model view matrix generated by ARToolKitPLus according to the orientation of the marker
*/
- (void)aRToolKitPlusWrapper:(ARToolKitPlusWrapper *)wrapper didDetectMarker:(int)markerID withConfidence:(float)confidence
		andComputeModelViewMatrix:(NSArray *)modelViewMatrix;

@end

/*!
 @author Benjamin Loulier
 
 @brief    This class is an objective-c wrapper for ARToolKitPlus
 
 ARToolKitPlus is written in C++, the aim of this class is makint it more Objective-c friendly
 by "hiding" the complexity of mixing C++ and objective-C code.
 This class contains objective-c methods which create ARToolKitPlus instances and invoke some
 C++ methods.
 */
@interface ARToolKitPlusWrapper : NSObject {
@private
	id _delegate;
	/*ARToolkit options*/
	BOOL _useBCHMarker;
	BOOL _useThinBorderMarker;
}

/*!
	@brief	The delegate will receive the datas returned by ARToolKit when a frame is processed.
*/
@property (nonatomic, assign) id delegate;

/*ARToolkit options*/

/*!
 @brief	Options to make ARToolKitPlus use BCH Markers instead of the regular ones (tested by Franck, thanks a lot !)
 */
@property (nonatomic, assign) BOOL useBCHMarker;
/*!
 @brief	Options to make ARToolKitPlus use markers with thin borders instead of the regular ones (untested)
 */
@property (nonatomic, assign) BOOL useThinBorderMarker;

/*!
	@brief	This method setup the marker detection with a sample image.

	@param	imageBuffer The sample image buffer
*/
- (void)setupWithImageBuffer:(CVImageBufferRef)imageBuffer;
/*!
 @brief	This method trigger the marker detection on an image buffer.
 
 This methods when the marker detection is over call its delegate to send it informations.
 See ARToolKitPlusWrapperDelegate.
 
 @param	imageBuffer The image buffer processed for marker detection
 */
- (void)detectMarkerInImageBuffer:(CVImageBufferRef)imageBuffer;

@end
