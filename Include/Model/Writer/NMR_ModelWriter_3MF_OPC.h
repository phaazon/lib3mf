/*++

Copyright (C) 2015 Microsoft Corporation (Original Author)
Copyright (C) 2015 netfabb GmbH

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

NMR_ModelWriter_3MF_OPC.h defines the 3MF Model Writer Class
for Win32. This model writer exports the in memory represenation into a 3MF file,
using the Windows OPC Library Functions.

--*/

#ifndef __NMR_MODELWRITER_3MF_OPC
#define __NMR_MODELWRITER_3MF_OPC

#include "Common/Platform/NMR_CComPtr.h"
#include "Model/Writer/NMR_ModelWriter_3MF.h" 
#include <Msopc.h>

namespace NMR {

	class CModelWriter_3MF_OPC : public CModelWriter_3MF {
	protected:
		nfInt32 m_nRelationIDCounter;

		// Package Parts and RelationShips
		CComPtr<IOpcPackage> m_pPackage;
		CComPtr<IOpcFactory> m_pFactory;
		CComPtr<IOpcPartSet> m_pPackagePartSet;
		CComPtr<IOpcRelationshipSet> m_pPackageRelationshipSet;

		CComPtr<IOpcPart> createOPCPart(_In_ LPCWSTR pwszUriString, _In_ LPCWSTR pwszContentType);
		CComPtr<IOpcPart> createOPCPartFromStream(_In_ LPCWSTR pwszUriString, _In_ LPCWSTR pwszContentType, _In_ IStream * pStream);
		CComPtr<IOpcPart> createOPCModelPart(_In_ LPCWSTR pwszUriString, _In_ LPCWSTR pwszContentType, _In_ CModel * pModel);

		CComPtr<IOpcRelationship> addRelationship(_In_ IOpcRelationshipSet * pRelationshipSet, _In_ LPCWSTR pwszRelationshipType, _In_ IOpcPart * pOPCPart);

		// These are OPC dependent functions
		virtual void createPackage(_In_ CModel * pModel);
		virtual void writePackageToStream(_In_ PExportStream pStream);
		virtual void releasePackage();

		void addTextureParts(_In_ CModel * pModel, _In_ CComPtr<IOpcPart> pModelPart);
	public:
		CModelWriter_3MF_OPC() = delete;
		CModelWriter_3MF_OPC(_In_ PModel pModel);
	};

}

#endif // __NMR_MODELWRITER_3MF_OPC
