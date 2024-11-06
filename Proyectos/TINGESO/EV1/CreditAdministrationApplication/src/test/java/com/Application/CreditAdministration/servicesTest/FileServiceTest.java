package com.Application.CreditAdministration.servicesTest;

import com.Application.CreditAdministration.entities.FileEntity;
import com.Application.CreditAdministration.repositories.FileRepository;
import com.Application.CreditAdministration.servicies.FileService;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.extension.ExtendWith;
import org.mockito.ArgumentMatchers;
import org.mockito.InjectMocks;
import org.mockito.Mock;
import org.mockito.junit.jupiter.MockitoExtension;
import org.springframework.dao.DataAccessException;
import org.springframework.mock.web.MockMultipartFile;
import java.io.IOException;
import static org.junit.jupiter.api.Assertions.*;
import static org.mockito.Mockito.*;

@ExtendWith(MockitoExtension.class)
public class FileServiceTest {

    @Mock
    private FileRepository fileRepository;

    @InjectMocks
    private FileService fileService;

    @Test
    public void whenUploadFile_thenReturnOne() throws IOException {
        //given
        long creditId = 1L;
        int type = 2;
        MockMultipartFile file = new MockMultipartFile("file", "test.txt", "text/plain", "test content".getBytes());

        //when
        int result = fileService.uploadFile(creditId, type, file);

        //then
        assertEquals(1, result);
        verify(fileRepository).save(ArgumentMatchers.any());
    }

    @Test
    public void whenDownloadFile_thenReturnFileEntity() {
        //given
        long creditId = 1L;
        int type = 2;
        FileEntity fileEntity = new FileEntity();
        fileEntity.setCreditId(creditId);
        fileEntity.setType(type);
        fileEntity.setFilename("test.txt");
        fileEntity.setFileContent("test content".getBytes());

        //when
        when(fileRepository.findByCreditIdAndType(creditId, type)).thenReturn(fileEntity);
        FileEntity result = fileService.downloadFile(creditId, type);

        //then
        assertNotNull(result);
        assertEquals(creditId, result.getCreditId());
        assertEquals(type, result.getType());
        assertEquals("test.txt", result.getFilename());
        assertArrayEquals("test content".getBytes(), result.getFileContent());
    }

    @Test
    public void whenDeleteFiles_thenReturnOne() throws Exception {
        //given
        long creditId = 1L;

        //when
        int result = fileService.deleteFiles(creditId);

        //then
        assertEquals(1, result);
        verify(fileRepository).deleteByCreditId(creditId);
    }

    @Test
    public void whenDeleteFiles_thenReturnZero() throws Exception {
        //given
        long creditId = 1L;

        //when
        doThrow(new DataAccessException("Database error") {}).when(fileRepository).deleteByCreditId(creditId);
        int result = fileService.deleteFiles(creditId);

        //then
        assertEquals(0, result);
        verify(fileRepository, times(1)).deleteByCreditId(creditId);
    }
}
