package com.example.demo.servicies;

import com.azure.storage.blob.BlobClient;
import com.azure.storage.blob.BlobContainerClient;
import com.azure.storage.blob.BlobServiceClient;
import com.azure.storage.blob.BlobServiceClientBuilder;
import com.example.demo.entities.fileEntity;
import com.example.demo.repositories.fileRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

@Service
public class fileService{

    @Autowired
    fileRepository FileRepository;

    private String connectionString;

    private String containerName;

    public fileEntity saveFile(fileEntity file){
        return FileRepository.save(file);
    }

    public fileEntity getInformation(long creditId, int type){
        return FileRepository.getByCreditIdAndType(creditId,type);
    }

    public String uploadFile(MultipartFile file) throws IOException {
        connectionString = "DefaultEndpointsProtocol=https;AccountName=<creditfiles>;AccountKey=<ZKqA/ii1ntkaDTDx5fdZGIDjMFwh5efNjRgwNcWh8MfmqefDSF1EX3ZdqYrJp3YLsnNRtg3uu3Td+ASt1G66oQ==>;EndpointSuffix=core.windows.net";
        containerName = "Tingeso";
        BlobServiceClient blobServiceClient = new BlobServiceClientBuilder().connectionString(connectionString).buildClient();
        BlobContainerClient containerClient = blobServiceClient.getBlobContainerClient(containerName);

        if (!containerClient.exists()) {
            containerClient.create();
        }

        BlobClient blobClient = containerClient.getBlobClient(file.getOriginalFilename());
        blobClient.upload(file.getInputStream(), file.getSize(), true);

        return blobClient.getBlobUrl();
    }

    public byte[] downloadFile(String fileName) throws IOException {
        connectionString = "DefaultEndpointsProtocol=https;AccountName=<creditfiles>;AccountKey=<ZKqA/ii1ntkaDTDx5fdZGIDjMFwh5efNjRgwNcWh8MfmqefDSF1EX3ZdqYrJp3YLsnNRtg3uu3Td+ASt1G66oQ==>;EndpointSuffix=core.windows.net";
        containerName = "Tingeso";
        BlobServiceClient blobServiceClient = new BlobServiceClientBuilder()
                .connectionString(connectionString)
                .buildClient();
        BlobContainerClient containerClient = blobServiceClient.getBlobContainerClient(containerName);
        BlobClient blobClient = containerClient.getBlobClient(fileName);

        if (!blobClient.exists()) {
            throw new FileNotFoundException("El archivo no existe en Azure Blob Storage.");
        }

        ByteArrayOutputStream outputStream = new ByteArrayOutputStream();
        blobClient.download(outputStream);
        return outputStream.toByteArray();
    }
}
