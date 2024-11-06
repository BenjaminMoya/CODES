FROM openjdk:17
ARG JAR_FILE=target/creditapp-backend.jar
COPY ${JAR_FILE} creditapp-backend.jar
ENTRYPOINT ["java", "-jar","/creditapp-backend.jar"]