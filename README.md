# Linux-IPC_Shared_Memory
Linux IPC of shared memory practice. sys/shm
## 說明:

使用WriteShm將資料載入Shared_Memory中，再利用ReadShm取出Shared_Memory資料

## 測試方式:

輸入WriteShm <keyId> <name> <No> <M/F> <Age> <Phone>，將資料寫到Shared_Memory中

輸入ReadShm <KeyId> 抓取Shared_Memory資料

### example:

WriteShm 868 AMO 9527 M 99 09123

ReadShm 868
