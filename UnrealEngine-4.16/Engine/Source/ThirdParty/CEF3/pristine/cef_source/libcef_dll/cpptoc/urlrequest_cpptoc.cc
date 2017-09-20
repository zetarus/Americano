// Copyright (c) 2016 The Chromium Embedded Framework Authors. All rights
// reserved. Use of this source code is governed by a BSD-style license that
// can be found in the LICENSE file.
//
// ---------------------------------------------------------------------------
//
// This file was generated by the CEF translator tool. If making changes by
// hand only do so within the body of existing method and function
// implementations. See the translator.README.txt file in the tools directory
// for more information.
//

#include "libcef_dll/cpptoc/request_cpptoc.h"
#include "libcef_dll/cpptoc/request_context_cpptoc.h"
#include "libcef_dll/cpptoc/response_cpptoc.h"
#include "libcef_dll/cpptoc/urlrequest_cpptoc.h"
#include "libcef_dll/ctocpp/urlrequest_client_ctocpp.h"


// GLOBAL FUNCTIONS - Body may be edited by hand.

CEF_EXPORT cef_urlrequest_t* cef_urlrequest_create(cef_request_t* request,
    struct _cef_urlrequest_client_t* client,
    cef_request_context_t* request_context) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  // Verify param: request; type: refptr_same
  DCHECK(request);
  if (!request)
    return NULL;
  // Verify param: client; type: refptr_diff
  DCHECK(client);
  if (!client)
    return NULL;
  // Unverified params: request_context

  // Execute
  CefRefPtr<CefURLRequest> _retval = CefURLRequest::Create(
      CefRequestCppToC::Unwrap(request),
      CefURLRequestClientCToCpp::Wrap(client),
      CefRequestContextCppToC::Unwrap(request_context));

  // Return type: refptr_same
  return CefURLRequestCppToC::Wrap(_retval);
}


namespace {

// MEMBER FUNCTIONS - Body may be edited by hand.

cef_request_t* CEF_CALLBACK urlrequest_get_request(
    struct _cef_urlrequest_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefRequest> _retval = CefURLRequestCppToC::Get(self)->GetRequest();

  // Return type: refptr_same
  return CefRequestCppToC::Wrap(_retval);
}

struct _cef_urlrequest_client_t* CEF_CALLBACK urlrequest_get_client(
    struct _cef_urlrequest_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefURLRequestClient> _retval = CefURLRequestCppToC::Get(
      self)->GetClient();

  // Return type: refptr_diff
  return CefURLRequestClientCToCpp::Unwrap(_retval);
}

cef_urlrequest_status_t CEF_CALLBACK urlrequest_get_request_status(
    struct _cef_urlrequest_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return UR_UNKNOWN;

  // Execute
  cef_urlrequest_status_t _retval = CefURLRequestCppToC::Get(
      self)->GetRequestStatus();

  // Return type: simple
  return _retval;
}

cef_errorcode_t CEF_CALLBACK urlrequest_get_request_error(
    struct _cef_urlrequest_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return ERR_NONE;

  // Execute
  cef_errorcode_t _retval = CefURLRequestCppToC::Get(self)->GetRequestError();

  // Return type: simple
  return _retval;
}

cef_response_t* CEF_CALLBACK urlrequest_get_response(
    struct _cef_urlrequest_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return NULL;

  // Execute
  CefRefPtr<CefResponse> _retval = CefURLRequestCppToC::Get(self)->GetResponse(
      );

  // Return type: refptr_same
  return CefResponseCppToC::Wrap(_retval);
}

void CEF_CALLBACK urlrequest_cancel(struct _cef_urlrequest_t* self) {
  // AUTO-GENERATED CONTENT - DELETE THIS COMMENT BEFORE MODIFYING

  DCHECK(self);
  if (!self)
    return;

  // Execute
  CefURLRequestCppToC::Get(self)->Cancel();
}

}  // namespace


// CONSTRUCTOR - Do not edit by hand.

CefURLRequestCppToC::CefURLRequestCppToC() {
  GetStruct()->get_request = urlrequest_get_request;
  GetStruct()->get_client = urlrequest_get_client;
  GetStruct()->get_request_status = urlrequest_get_request_status;
  GetStruct()->get_request_error = urlrequest_get_request_error;
  GetStruct()->get_response = urlrequest_get_response;
  GetStruct()->cancel = urlrequest_cancel;
}

template<> CefRefPtr<CefURLRequest> CefCppToC<CefURLRequestCppToC,
    CefURLRequest, cef_urlrequest_t>::UnwrapDerived(CefWrapperType type,
    cef_urlrequest_t* s) {
  NOTREACHED() << "Unexpected class type: " << type;
  return NULL;
}

#ifndef NDEBUG
template<> base::AtomicRefCount CefCppToC<CefURLRequestCppToC, CefURLRequest,
    cef_urlrequest_t>::DebugObjCt = 0;
#endif

template<> CefWrapperType CefCppToC<CefURLRequestCppToC, CefURLRequest,
    cef_urlrequest_t>::kWrapperType = WT_URLREQUEST;
