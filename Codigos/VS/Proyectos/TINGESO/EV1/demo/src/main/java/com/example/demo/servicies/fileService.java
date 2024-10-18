package com.example.demo.servicies;

import com.example.demo.entities.fileEntity;
import com.example.demo.repositories.fileRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import org.springframework.web.multipart.MultipartFile;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@Service
public class fileService {

    @Autowired
    fileRepository FileRepository;

    public void saveFile(fileEntity file){
        FileRepository.save(file);
    }

    public String storeFile(MultipartFile file) throws IOException {
        Path storagePath = Paths.get("uploads");
        if(!Files.exists(storagePath)){
            Files.createDirectories(storagePath);
        }

        String filename = file.getOriginalFilename();
        if(filename == null || filename.isEmpty()){
            throw new IOException("El archivo no tiene un nombre valido.");
        }

        Path filePath = storagePath.resolve(filename);

        Files.copy(file.getInputStream(),filePath);

        return filePath.toString();
    }
}
