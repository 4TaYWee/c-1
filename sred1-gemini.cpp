/*
 I'd be glad to provide the C++ code for changing file permissions on a Windows system, incorporating the best aspects of the previous responses and addressing potential shortcomings:
 
 C++
 */
 #include <windows.h>
 #include <aclapi.h>
 #include <iostream>
 #include <string>
 
 // Function to check for errors and display informative messages
 void CheckError(const std::wstring& msg, DWORD error) {
 	if (error != ERROR_SUCCESS) {
 		FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
 		NULL, error, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
 		(LPTSTR)LocalAlloc(LMEM_FIXED, MAX_PATH), 0, (LPDWORD)NULL);
 		std::wcerr << msg << L": " << (LPWSTR)LocalAlloc(LMEM_FIXED, MAX_PATH) << std::endl;
 		LocalFree(LocalAlloc(LMEM_FIXED, MAX_PATH));
 	}
 }
 
 // Function to get the current DACL of a file
 bool GetFileDacl(const std::wstring& filepath, PSECURITY_DESCRIPTOR* psd) {
 	DWORD dwDesiredAccess = GENERIC_READ | ACL_READ;
 	HANDLE hFile = CreateFile(filepath.c_str(), dwDesiredAccess, FILE_SHARE_READ,
 	NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
 	if (hFile == INVALID_HANDLE_VALUE) {
 		CheckError(L"CreateFile failed", GetLastError());
 		return false;
 	}
 	
 	BOOL result = GetSecurityInfo(hFile, DACL_SECURITY_INFORMATION, psd, NULL, NULL, NULL, NULL);
 	CloseHandle(hFile);
 	return result != FALSE;
 }
 
 // Function to modify DACL to grant/revoke permissions for a specific user/group
 bool ModifyDaclForPermission(PSECURITY_DESCRIPTOR psd, const std::wstring& username, DWORD access_mask, bool grant) {
 	EXPLICIT_ACCESS ea;
 	ZeroMemory(&ea, sizeof(EXPLICIT_ACCESS));
 	
 	// Set appropriate flags based on grant/revoke operation
 	ea.grfAccessPermissions = access_mask;
 	ea.grfInheritance = SUBTREE_AND_OBJECT_INHERIT | CONTAINER_INHERIT;
 	ea.Trustee.pMultipleTrustee = NULL;
 	ea.Trustee.ptstrName = (LPTSTR)username.c_str();
 	
 	SID_IDENTIFIER_AUTHORITY sia = SECURITY_NT_AUTHORITY;
 	if (!AllocateAndInitializeSid(&SecurityImpersonationSid, 1, &sia, 0)) {
 		CheckError(L"AllocateAndInitializeSid failed", GetLastError());
 		return false;
 	}
 	
 	ea.Trustee.ptstrNameMode = (grant ? NAME_FOR_USER : NAME_DELETED_WITH_AUTHORITY);
 	ea.Trustee.ptstrNameType = SID_AND_ATTRIBUTES;
 	ea.Trustee.dwAuthenticatedSidLength = sizeof(SID);
 	ea.Trustee.uChangeType = grant ? GRANT_ACCESS : REVOKE_ACCESS;
 	ea.Trustee.uEnumType = SET_ACCESS;
 	
 	// Set the appropriate SID based on user/group name
 	if (!CopySid(sizeof(SID), (PSID)SecurityImpersonationSid, &ea.Trustee.sid)) {
 		CheckError(L"CopySid failed", GetLastError());
 		FreeSid(SecurityImpersonationSid);
 		return false;
 	}
 	
 	ACL_SIZE_INFORMATION aclSizeInfo;
 	if (GetAclInformation(psd, GetAclFromContainer(psd, DACL_SECURITY_INFORMATION), &aclSizeInfo, sizeof(ACL_SIZE_INFORMATION)) == FALSE) {
 		CheckError(L"GetAclInformation failed", GetLastError());
 		FreeSid(SecurityImpersonationSid);
 		return false;
 	}
 	
 	PACL newDacl = (PACL)LocalAlloc(LMEM_FIXED, aclSizeInfo.AclSize + sizeof(ACL));
 	if (newDacl == NULL) {
 		CheckError(L"LocalAlloc failed", GetLastError());
 		FreeSid(SecurityImpersonationSid);
 		return false;
 	}
 	
 	if (!InitializeAcl(newDacl, aclSizeInfo.AclSize, ACL_REVISION)) {
 		CheckError(L"InitializeAcl failed", GetLastError());
 		LocalFree(newDacl);
 		FreeSid(SecurityImpersonationSid);
 		return false;
 		
 		/*
 		Źródła
 		1. https://github.com/0x0002/Project1
*/
