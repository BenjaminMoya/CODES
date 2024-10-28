package com.example.demo.controllers;

import com.example.demo.entities.userEntity;
import com.example.demo.servicies.userService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import java.util.ArrayList;
import java.util.Map;

@RestController
@RequestMapping("/api/user")
@CrossOrigin("*")
public class userController {

    @Autowired
    userService UserService;

    @GetMapping("/get")
    public ResponseEntity<ArrayList<userEntity>> listUsers(){
        ArrayList<userEntity> users = UserService.getUsers();
        return ResponseEntity.ok(users);
    }

    @GetMapping("/getById/{userId}")
    public ResponseEntity<userEntity> getUserById(@PathVariable Long userId) {
        userEntity user = UserService.getUserById(userId);
        return ResponseEntity.ok(user);
    }

    @GetMapping("/getByRut/{userRut}")
    public ResponseEntity<userEntity> getUserByRut(@PathVariable String userRut){
        userEntity user = UserService.getUserByRut(userRut);
        return ResponseEntity.ok(user);
    }

    @GetMapping("/getByEmail/{userEmail}")
    public ResponseEntity<userEntity> getUserByEmail(@PathVariable String userEmail){
        userEntity user = UserService.getUserByEmail(userEmail);
        return ResponseEntity.ok(user);
    }

    @PostMapping("/save")
    public ResponseEntity<userEntity> saveUser(@RequestBody userEntity user) {
        userEntity newUser = UserService.saveUser(user);
        return ResponseEntity.ok(newUser);
    }

    @PostMapping("/login")
    public ResponseEntity<userEntity> login(@RequestBody userEntity user){
        return ResponseEntity.ok(UserService.login(user.getUserEmail(),user.getUserPassword()));
    }

    @PostMapping("/zero/{userId}")
    public int zeroSaving(@PathVariable long userId){
        return UserService.zeroSaving(userId);
    }

    @PutMapping("/update")
    public ResponseEntity<userEntity> updateUser(@RequestBody userEntity user){
        userEntity userUpdated = UserService.updateUser(user);
        return ResponseEntity.ok(userUpdated);
    }

    @PostMapping("/transfer")
    public double transferAmount(@RequestBody Map<String, Object> body){
        long userId = Long.parseLong(body.get("userId").toString());
        long creditId = Long.parseLong(body.get("creditId").toString());
        return UserService.transferAmount(userId,creditId);
    }

    @DeleteMapping("/delete/{userId}")
    public ResponseEntity<Boolean> deleteUserById(@PathVariable Long userId) throws Exception {
        var isDeleted = UserService.deleteUser(userId);
        return ResponseEntity.ok(isDeleted);
    }
}
