package test

import (
	"os"
	"testing"
	"fmt"
	"io"
)

func TestCreate(t *testing.T) {
	f, err := os.Create("TestCreate_test.txt"); if err != nil {
		panic(err)
	}
	defer f.Close()
}

func TestMkdir(t *testing.T) {
	err := os.Mkdir("TestMkdir_dir", os.ModePerm); if err != nil {
		panic(err)
	}

}

func TestMkdirAll(t *testing.T) {
	err := os.MkdirAll("TestMkdir_dir/a/a", os.ModePerm); if err != nil {
		panic(err)
	}
}

func TestRemove(t *testing.T) {
	err := os.Remove("TestMkdir_dir/a/a"); if err != nil {
		panic(err)
	}
}

func TestRemoveAll(t *testing.T) {
	err := os.RemoveAll("TestMkdir_dir"); if err != nil {
		panic(err)
	}
}

func TestGetwd(t *testing.T) {
	dir, err := os.Getwd(); if err != nil {
		panic(err)
	}

	fmt.Printf("%s\n", dir)
}

func TestChdir(t *testing.T) {
	err := os.Chdir("/"); if err != nil {
		panic(err)
	}

	dir, err := os.Getwd(); if err != nil {
		panic(err)
	}

	fmt.Printf("%s\n", dir)
}

func TestTempDir(t *testing.T) {
	dir := os.TempDir()

	fmt.Printf("%s\n", dir)
}

func TestRename(t *testing.T) {
	f, err := os.Create("test.txt"); if err != nil {
		panic(err)
	}
	defer f.Close()

	err = os.Rename("test.txt", "test_new_name.txt"); if err != nil {
		panic(err)
	}
}

func TestChmod(t *testing.T) {
	err := os.Chmod("test_new_name.txt", 0777); if err != nil {
		panic(err)
	}
}

func TestChown(t *testing.T) {
	err := os.Chown("test_new_name.txt", 1000, 1000); if err != nil {
		panic(err)
	}
}

func TestStat(t *testing.T) {
	f, err := os.OpenFile("test_new_name.txt", os.O_RDWR, 0644); if err != nil {
		panic(err)
	}
	defer f.Close()

	fi, err := f.Stat(); if err != nil {
		panic(err)
	}

	fmt.Printf("Name: %s\nSize: %d\nMode: %v\n", fi.Name(), fi.Size(), fi.Mode())
}

func TestRead(t *testing.T) {
	f, err := os.OpenFile("test_new_name.txt", os.O_RDWR, 0644); if err != nil {
		panic(err)
	}
	defer f.Close()

	var body []byte

	for {
		buf := make([]byte, 10)
		n, err := f.Read(buf); if err == io.EOF {
			break
		}
		body = append(body, buf[:n]...)
	}

	fmt.Printf("%s\n", body)
}

func TestReadAt(t *testing.T) {
	f, err := os.OpenFile("test_new_name.txt", os.O_RDWR, 0644); if err != nil {
		panic(err)
	}
	defer f.Close()

	buf := make([]byte, 10)
	_, err = f.ReadAt(buf, 11); if err == io.EOF {
	}
	fmt.Printf("%s\n", buf)
}

func TestReadDir(t *testing.T) {

	 ds, err := os.ReadDir("t"); if err != nil {
		panic(err)
	 }

	 for _, v := range ds {
		fmt.Printf("Name: %s\n", v.Name())
	 }

}

func TestFileSeek(t *testing.T) {
	f, err := os.OpenFile("test_new_name.txt", os.O_RDWR | os.O_CREATE, 0755); if err != nil {
		panic(err)
	}
	defer f.Close()

	f.Seek(8, 0)
	buf := make([]byte, 10)
	n, _ := f.Read(buf)
	fmt.Printf("%s\n", buf[:n])
}

func TestFileWrite(t *testing.T) {
	f, err := os.OpenFile("test_new_name.txt", os.O_RDWR | os.O_APPEND, 0755); if err != nil {
		panic(err)
	}
	defer f.Close()

	n, err := f.Write([]byte("hello world.\n")); if err != nil {
		panic(err)
	}

	fmt.Printf("write size: %d\n", n)
}

func TestFileWriteString(t *testing.T) {
	f, err := os.OpenFile("test_new_name.txt", os.O_RDWR | os.O_APPEND, 0755); if err != nil {
		panic(err)
	}
	defer f.Close()

	n, err := f.WriteString("hello world.\n"); if err != nil {
		panic(err)
	}

	fmt.Printf("write size: %d\n", n)
}

func TestFileWriteAt(t *testing.T) {
	f, err := os.OpenFile("test_new_name.txt", os.O_RDWR, 0755); if err != nil {
		panic(err)
	}
	defer f.Close()

	_, err = f.WriteAt([]byte("testtest"), 5); if err != nil {
		panic(err)
	}

}

func TestId(t *testing.T) {
	fmt.Printf("os.Getpid(): %v\n", os.Getpid())
	fmt.Printf("os.Getppid(): %v\n", os.Getppid())
}
