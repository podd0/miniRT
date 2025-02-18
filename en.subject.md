Transcription of the **miniRT – My first RayTracer with miniLibX** subject in English:

---

# **miniRT**  
**My first RayTracer with miniLibX**  

### **Summary:**  
This project is an introduction to the fascinating world of Ray Tracing.  
Once completed, you will be able to render simple computer-generated images and will no longer be afraid of implementing complex mathematical formulas.  

**Version:** 8  

---

## **Table of Contents**  

I. Introduction  
II. Common Instructions  
III. Mandatory Part - miniRT  
IV. Bonus Part  
V. Examples  
VI. Submission and Peer-Evaluation  

---

## **Chapter I - Introduction**  

When it comes to rendering 3D computer-generated images, there are two possible approaches:  

1. **Rasterization**, used by most graphics engines due to its efficiency.  
2. **Ray Tracing**, first developed in 1968 and improved over time. It remains computationally more expensive than rasterization and is still not fully suited for real-time applications, but it produces a much higher degree of visual realism.  

> **Objective of miniRT:**  
To prove that you can implement mathematical and physics formulas without being a mathematician. This project covers only the most basic ray tracing features.  

---

## **Chapter II - Common Instructions**  

- The project must be written in **C**.  
- The code must comply with the **Norm**. A single norm error results in a **0** grade.  
- The program must not crash unexpectedly (segmentation fault, bus error, double free, etc.).  
- All dynamically allocated memory must be correctly freed. No memory leaks are allowed.  
- A **Makefile** is required and must support `all`, `clean`, `fclean`, `re`, and `bonus`.  
- The Makefile must **not relink**.  
- If the project allows the use of **libft**, it must be included as source in the repository.  
- It is recommended to create test programs for debugging, even though they won’t be graded.  
- The project must be submitted to the assigned Git repository.  

---

## **Chapter III - Mandatory Part**  

### **miniRT – Specifications**  

- **Program name**: `miniRT`  
- **Turn-in files**: All source files  
- **Makefile**: Must support `all`, `clean`, `fclean`, `re`, `bonus`  
- **Arguments**: A scene description file with `.rt` extension  
- **Allowed functions**:  
  - `open, close, read, write, printf, malloc, free, perror, strerror, exit`  
  - All functions from the math library `-lm`  
  - All functions from **miniLibX**  

- **Libft authorized**: **Yes**  
- **Description**: The program must generate images using the Ray Tracing protocol.  

---

### **Main Requirements**  

1. **Use miniLibX** (installed system-wide or compiled with the project).  
2. **Smooth window management** (switching windows, minimization, resizing).  
3. **Three required geometric objects**:  
   - **Plane**  
   - **Sphere**  
   - **Cylinder**  
4. **Correct intersection handling and rendering of object interiors**.  
5. **Transformation support** (translation and rotation for objects, lights, and cameras).  
6. **Lighting management**:  
   - Ambient lighting  
   - Hard shadows  
   - Diffuse lighting  
7. **Window interaction**:  
   - Pressing `ESC` must close the window and exit the program.  
   - Clicking the `X` button must correctly close the application.  
8. **Scene description file (`.rt`)**  
   - Elements can be placed in any order.  
   - Separated by spaces or line breaks.  

---

### **Scene File Format (`.rt`)**  

#### **Scene Elements and Syntax**  

- **Ambient Light**:  
  ```
  A 0.2 255,255,255
  ```
  - `A`: Identifier  
  - `0.2`: Intensity (range [0.0, 1.0])  
  - `255,255,255`: RGB color  

- **Camera**:  
  ```
  C -50.0,0,20 0,0,1 70
  ```
  - `C`: Identifier  
  - `-50.0,0,20`: Coordinates  
  - `0,0,1`: Normalized orientation vector  
  - `70`: FOV (Field of View)  

- **Light Source**:  
  ```
  L -40.0,50.0,0.0 0.6 10,0,255
  ```
  - `L`: Identifier  
  - `-40.0,50.0,0.0`: Coordinates  
  - `0.6`: Light intensity (range [0.0, 1.0])  

- **Sphere**:  
  ```
  sp 0.0,0.0,20.6 12.6 10,0,255
  ```
  - `sp`: Identifier  
  - `0.0,0.0,20.6`: Center  
  - `12.6`: Diameter  

- **Plane**:  
  ```
  pl 0.0,0.0,-10.0 0.0,1.0,0.0 0,0,225
  ```
  - `pl`: Identifier  
  - `0.0,0.0,-10.0`: A point on the plane  
  - `0.0,1.0,0.0`: Normalized normal vector  

- **Cylinder**:  
  ```
  cy 50.0,0.0,20.6 0.0,0.0,1.0 14.2 21.42 10,0,255
  ```
  - `cy`: Identifier  
  - `50.0,0.0,20.6`: Center  
  - `14.2`: Diameter  
  - `21.42`: Height  

- **Error Handling in Scene Files**:  
  If any misconfiguration is detected, the program must exit and display an explicit error message.  

---

## **Chapter IV - Bonus Part**  

> **Bonuses will be graded only if the mandatory part is PERFECT.**  

Possible enhancements:  
- **Full Phong Reflection Model**  
- **Color disruption (checkerboard effect)**  
- **Colored and multi-spot lights**  
- **Additional objects (cone, hyperboloid, paraboloid, etc.)**  
- **Bump mapping for texture handling**  

Scene files may be modified to support these features.  

---

## **Chapter V - Examples**  

The document includes images of sample rendered scenes with:  
- Sphere with point light  
- Cylinder with lighting  
- Cone, plane, and light source  
- A scene with multiple elements from different camera angles  
- Shadows and multiple light sources  

---

## **Chapter VI - Submission and Peer-Evaluation**  

- The project must be submitted via Git.  
- Verify file names before submission.  
- Test the code before evaluation.  
