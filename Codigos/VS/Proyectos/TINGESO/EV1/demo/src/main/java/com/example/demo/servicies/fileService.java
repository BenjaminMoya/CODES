package com.example.demo.servicies;

import com.azure.storage.blob.BlobClient;
import com.azure.storage.blob.BlobContainerClient;
import com.azure.storage.blob.BlobServiceClient;
import com.azure.storage.blob.BlobServiceClientBuilder;
import com.example.demo.entities.fileEntity;
import com.example.demo.repositories.fileRepository;
import jakarta.transaction.Transactional;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.MediaType;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.ByteArrayOutputStream;
import java.io.FileNotFoundException;
import java.io.IOException;

@Service
public class fileService {

    @Autowired
    fileRepository FileRepository;

    public int uploadFile(long creditId,int type,MultipartFile file) throws IOException {
        fileEntity newFile = new fileEntity();
        newFile.setCreditId(creditId);
        newFile.setType(type);
        newFile.setFilename(file.getOriginalFilename());
        newFile.setFileContent(file.getBytes());
        FileRepository.save(newFile);
        return 1;
    }

    @Transactional
    public fileEntity downloadFile(long creditId,int type){
        return FileRepository.getByCreditIdAndType(creditId,type);
    }

    public int deleteFiles(long creditId) throws Exception {
        try{
            FileRepository.deleteByCreditId(creditId);
            return 1;
        } catch (Exception e) {
            return 0;
        }
    }

}
