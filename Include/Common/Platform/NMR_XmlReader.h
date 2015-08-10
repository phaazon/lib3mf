/*++

Copyright (C) 2015 Microsoft Corporation
Copyright (C) 2015 netfabb GmbH (Original Author)

All rights reserved.

Redistribution and use in source and binary forms, with or without modification,
are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

Abstract:

NMR_XMLReader.h defines a XML reader class in a portable way.

--*/

#ifndef __NMR_XMLREADER
#define __NMR_XMLREADER

#include "Common/Platform/NMR_ImportStream.h"

namespace NMR {

	enum eXmlReaderNodeType {
		XMLREADERNODETYPE_UNKNOWN,
		XMLREADERNODETYPE_STARTELEMENT,
		XMLREADERNODETYPE_ENDELEMENT,
		XMLREADERNODETYPE_TEXT
	};

	class CXmlReader {
  private:
		PImportStream m_pImportStream;
	public:
		CXmlReader(_In_ PImportStream pImportStream);

		virtual void GetLocalName(_Outptr_result_buffer_maybenull_(*pcwchLocalName + 1) const nfWChar ** ppwszLocalName, _Out_opt_ nfUint32 *pcwchLocalName) = 0;
		virtual void GetValue(_Outptr_result_buffer_maybenull_(*pcwchValue + 1)  const nfWChar ** ppwszValue, _Out_opt_  nfUint32 *pcwchValue) = 0;
		virtual void GetNamespaceURI(_Outptr_result_buffer_maybenull_(*pcwchValue + 1)  const nfWChar ** ppwszValue, _Out_opt_  nfUint32 *pcwchValue) = 0;

		virtual nfBool Read(_Out_ eXmlReaderNodeType & NodeType) = 0;
		virtual nfBool IsEOF() = 0;
		virtual nfBool IsEmptyElement() = 0;
		virtual nfBool MoveToFirstAttribute() = 0;
		virtual nfBool MoveToNextAttribute() = 0;
		virtual nfBool IsDefault() = 0;
	};

	typedef std::shared_ptr<CXmlReader> PXmlReader;

}

#endif // __NMR_XMLREADER
