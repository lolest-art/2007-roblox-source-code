#pragma once

// Minimal replacement. Boost config normally defines BOOST_* macros.
// We only need to satisfy the include; the header is empty for our
// purposes.

#define BOOST_NO_CV_SPECIALIZATIONS
#define BOOST_NO_CV_VOID_SPECIALIZATIONS