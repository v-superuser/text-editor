// Internal interface for editor backends
//
// The reason why structures are defined in an internal interface is such that
// no external accessor can modify structure-internal fields except through
// pre-defined APIs. This greatly cuts down on the requirement for defensive
// programming except at the interface. Also localizes errors to being within
// the editor code.

#pragma once

#include <editor.h>

// An editor backend
struct editor_backend {
	const char *name;					                    // Backend name
	const char *desc;					                    // Description
	struct editor_buf* (*new) ();				            // New empty buffer
	struct editor_buf* (*new_with_str) (const char *str);	// New buffer with str
    void (*close) (struct editor_buf *buf);                 // Clean up resources
};

// Define the editor buffer structure
struct editor_buf {
	struct editor_backend *backend;	// The backend for this buffer
	void *data;			            // Backend-specific data
};
