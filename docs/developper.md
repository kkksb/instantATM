# MySQLの接続

ユーザ：root
パスワード：instant

# コンテナの起動と実行

docker build -t c_dev_env .
docker run -d --privileged -it --name "c_dev_env" --cap-add=SYS_PTRACE --security-opt="seccomp=unconfined" c_dev_env /sbin/init 
docker exec -it <イメージのID> /bin/bash
