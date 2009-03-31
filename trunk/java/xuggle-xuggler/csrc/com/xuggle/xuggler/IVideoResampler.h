/*
 * Copyright (c) 2008-2009 by Xuggle Inc. All rights reserved.
 *
 * It is REQUESTED BUT NOT REQUIRED if you use this library, that you let
 * us know by sending e-mail to info@xuggle.com telling us briefly how you're
 * using the library and what you like or don't like about it.
 *
 * This library is free software; you can redistribute it and/or modify it under the
 * terms of the GNU Lesser General Public License as published by the Free Software
 * Foundation; either version 2.1 of the License, or (at your option) any later
 * version.
 *
 * This library is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
 * PARTICULAR PURPOSE. See the GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License along
 * with this library; if not, write to the Free Software Foundation, Inc.,
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
#ifndef IVIDEORESAMPLER_H_
#define IVIDEORESAMPLER_H_

#include <com/xuggle/ferry/RefCounted.h>
#include <com/xuggle/xuggler/Xuggler.h>
#include <com/xuggle/xuggler/IPixelFormat.h>
#include <com/xuggle/xuggler/IVideoPicture.h>
#include <com/xuggle/xuggler/IProperty.h>

namespace com { namespace xuggle { namespace xuggler
  {

  /**
   * Converts {@link IVideoPicture} objects of a given width, height and format to a new
   * width, height or format.
   * <p>
   * This object is only active in GPL-licensed version of the Xuggler.  You can
   * use the {@link #isSupported(Feature)} to determine if you can use this object (or
   * the make(...) methods will also return null.
   * </p>
   */
  class VS_API_XUGGLER IVideoResampler : public com::xuggle::ferry::RefCounted
  {
  public:

    /**
     * Features that the VideoResampler may optionally support.
     */
    typedef enum {
      FEATURE_IMAGERESCALING,
      FEATURE_COLORSPACECONVERSION,
    } Feature;

    /**
     * @return The width we expect on the input frame to the resampler.
     */
    virtual int32_t getInputWidth()=0;

    /**
     * @return The height we expect on the input frame to the resampler.
     */
    virtual int32_t getInputHeight()=0;

    /**
     * @return The pixel format we expect on the input frame to the resampler.
     */
    virtual IPixelFormat::Type getInputPixelFormat()=0;

    /**
     * @return The width we will resample the output frame to
     */
    virtual int32_t getOutputWidth()=0;

    /**
     * @return The height we will resample the output frame to
     */
    virtual int32_t getOutputHeight()=0;

    /**
     * @return The pixel format we will resample the output frame to
     */
    virtual IPixelFormat::Type getOutputPixelFormat()=0;

    /**
     *
     * Resample pInFrame to pOutFrame based on the resampler parameters.
     *
     * Resamples the pInFrame based on the parameters set when
     * this resampler was constructed.
     *
     * @param pOutFrame The frame we'll resample to.  Check
     *     pOutFrame->isComplete() after the call.
     * @param pInFrame THe frame we'll resample from.
     *
     * @return >= 0 on success; <0 on error.
     */
    virtual int32_t resample(IVideoPicture *pOutFrame, IVideoPicture *pInFrame)=0;

    /*
     * Added for 1.19
     */

    /**
     * Returns the total number of settable properties on this object
     * 
     * @return total number of options (not including constant definitions)
     */
    virtual int32_t getNumProperties()=0;
    
    /**
     * Returns the name of the numbered property.
     * 
     * @param propertyNo The property number in the options list.
     *   
     * @return an IProperty value for this properties meta-data
     */
    virtual IProperty *getPropertyMetaData(int32_t propertyNo)=0;

    /**
     * Returns the name of the numbered property.
     * 
     * @param name  The property name.
     *   
     * @return an IProperty value for this properties meta-data
     */
    virtual IProperty *getPropertyMetaData(const char *name)=0;
    
    /**
     * Sets a property on this Object.
     * 
     * All AVOptions supported by the underlying AVClass are supported.
     * 
     * @param name The property name.  For example "b" for bit-rate.
     * @param value The value of the property. 
     * 
     * @return >= 0 if the property was successfully set; <0 on error
     */
    virtual int32_t setProperty(const char *name, const char* value)=0;


    /**
     * Looks up the property 'name' and sets the
     * value of the property to 'value'.
     * 
     * @param name name of option
     * @param value Value of option
     * 
     * @return >= 0 on success; <0 on error.
     */
    virtual int32_t setProperty(const char* name, double value)=0;
    
    /**
     * Looks up the property 'name' and sets the
     * value of the property to 'value'.
     * 
     * @param name name of option
     * @param value Value of option
     * 
     * @return >= 0 on success; <0 on error.
     */
    virtual int32_t setProperty(const char* name, int64_t value)=0;
    
    /**
     * Looks up the property 'name' and sets the
     * value of the property to 'value'.
     * 
     * @param name name of option
     * @param value Value of option
     * 
     * @return >= 0 on success; <0 on error.
     */
    virtual int32_t setProperty(const char* name, bool value)=0;
    
    /**
     * Looks up the property 'name' and sets the
     * value of the property to 'value'.
     * 
     * @param name name of option
     * @param value Value of option
     * 
     * @return >= 0 on success; <0 on error.
     */
    virtual int32_t setProperty(const char* name, IRational *value)=0;

#ifdef SWIG
    %newobject getPropertyAsString(const char*);
    %typemap(newfree) char * "delete [] $1;";
#endif
    /**
     * Gets a property on this Object.
     * 
     * Note for C++ callers; you must free the returned array with
     * delete[] in order to avoid a memory leak.  Other language
     * folks need not worry.
     * 
     * @param name property name
     * 
     * @return an string copy of the option value, or null if the option doesn't exist.
     */
    virtual char * getPropertyAsString(const char* name)=0;

    /**
     * Gets the value of this property, and returns as a double;
     * 
     * @param name name of option
     * 
     * @return double value of property, or 0 on error.
     */
    virtual double getPropertyAsDouble(const char* name)=0;

    /**
     * Gets the value of this property, and returns as an long;
     * 
     * @param name name of option
     * 
     * @return long value of property, or 0 on error.
     */
    virtual int64_t getPropertyAsLong(const char* name)=0;

    /**
     * Gets the value of this property, and returns as an IRational;
     * 
     * @param name name of option
     * 
     * @return long value of property, or 0 on error.
     */
    virtual  IRational *getPropertyAsRational(const char* name)=0;

    /**
     * Gets the value of this property, and returns as a boolean
     * 
     * @param name name of option
     * 
     * @return boolean value of property, or false on error.
     */
    virtual bool getPropertyAsBoolean(const char* name)=0;

    /**
     * Get a new video resampler.  Returns null if {@link #isSupported(Feature)} returns false.
     *
     * @param outputWidth The width in pixels you want to output frame to have.
     * @param outputHeight The height in pixels you want to output frame to have.
     * @param outputFmt The pixel format of the output frame.
     * @param inputWidth The width in pixels the input frame will be in.
     * @param inputHeight The height in pixels the input frame will be in.
     * @param inputFmt The pixel format of the input frame.
     * @return a new object, or null if we cannot allocate one.
     */
    static IVideoResampler* make(
        int32_t outputWidth, int32_t outputHeight,
        IPixelFormat::Type outputFmt,
        int32_t inputWidth, int32_t inputHeight,
        IPixelFormat::Type inputFmt);

    /**
     * Returns true if the asked for feature is supported.
     *
     * @param aFeature The feature you want to find out is supported.
     * @return true if the IVideoResampler supports this feature; false otherwise.
     */
    static bool isSupported(Feature aFeature);

  protected:
    IVideoResampler();
    virtual ~IVideoResampler();
  };

  }}}

#endif /*IVIDEORESAMPLER_H_*/