package com.example.demo.entities;

import jakarta.persistence.*;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Entity
@Table(name = "files")
@Data
@NoArgsConstructor
@AllArgsConstructor
public class fileEntity {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Column(unique = true,nullable = false)
    private long fileId;

    private long fileCreditId;
    private String fileName;
    private String filePath;

    // 0 = CI, 1 = CA, 2 = HC, 3 = EPV, 4 = EFN, 5 = PLN, 6 = PR, 7 = CAA
    private int type;
}
